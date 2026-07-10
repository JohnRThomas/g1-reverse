#!/usr/bin/env python3
"""
Structure Modification System
Reads original struct definition and applies field modifications
"""

import re
import sys
from dataclasses import dataclass
from typing import List, Dict, Tuple, Optional


@dataclass
class Field:
    offset: int
    name: str
    type_str: str
    size: int
    comment: str = ""
    is_gap: bool = False
    is_array: bool = False
    array_size: int = 1


class StructParser:
    def __init__(self):
        self.fields: List[Field] = []
        self.struct_name = ""
        self.struct_size = 0

    def parse_struct(self, content: str) -> None:
        """Parse struct definition from IDA-style format"""
        lines = content.strip().split('\n')

        # Parse struct header
        header_match = re.match(r'(\w+)\s+struct\s+(\w+)\s*//\s*sizeof=0x([0-9A-Fa-f]+)', lines[0])
        if header_match:
            self.struct_name = header_match.group(2)
            self.struct_size = int(header_match.group(3), 16)

        for line in lines:
            # Skip struct header and braces
            if 'struct' in line or '{' in line or '}' in line or not line.strip():
                continue

            # Parse field definition
            # Format: offset type name; // comment
            field_match = re.match(
                r'([0-9A-Fa-f]+)\s+((?:unsigned\s+)?(?:struct\s+)?[\w\s*]+?)(\w+)(?:\[(\d+)\])?;?\s*(?://\s*(.*))?',
                line)
            if field_match:
                offset = int(field_match.group(1), 16)
                type_str = field_match.group(2).strip()
                name = field_match.group(3)
                array_size_str = field_match.group(4)
                comment = field_match.group(5) or ""

                # Determine if it's a gap field
                is_gap = name.startswith('gap_') or name == 'remaining'

                # Calculate field size
                size = self._calculate_field_size(type_str, array_size_str)
                is_array = array_size_str is not None
                array_size = int(array_size_str) if array_size_str else 1

                field = Field(
                    offset=offset,
                    name=name,
                    type_str=type_str,
                    size=size,
                    comment=comment,
                    is_gap=is_gap,
                    is_array=is_array,
                    array_size=array_size
                )
                self.fields.append(field)

        # Sort fields by offset
        self.fields.sort(key=lambda f: f.offset)

    def _calculate_field_size(self, type_str: str, array_size_str: Optional[str]) -> int:
        """Calculate field size based on type"""
        base_size = 1  # default for __int8

        if 'void *' in type_str or '*' in type_str:
            base_size = 4  # pointer size
        elif '__int32' in type_str:
            base_size = 4
        elif '__int16' in type_str:
            base_size = 2
        elif 'struct projector_controller_t' in type_str:
            base_size = 0x378  # from original script

        if array_size_str:
            return base_size * int(array_size_str)
        return base_size


class ModificationParser:
    def __init__(self):
        self.modifications: List[Tuple[str, int, str, str]] = []

    def parse_modifications(self, content: str) -> None:
        """Parse modification definitions"""
        lines = content.strip().split('\n')

        for line in lines:
            line = line.strip()
            if not line or line.startswith('#'):
                continue

            # Parse: device_info->gap_10BC[10] -> __int8 new_field_name
            match = re.match(r'device_info->(\w+)(?:\[(\d+)\])?\s*->\s*([\w\s*]+?)\s+(\w+)', line)
            if match:
                field_name = match.group(1)
                array_index = int(match.group(2)) if match.group(2) else None
                new_type = match.group(3).strip()
                new_name = match.group(4)

                self.modifications.append((field_name, array_index, new_type, new_name))


class StructModifier:
    def __init__(self, original_struct: StructParser):
        self.original = original_struct
        self.new_fields: List[Field] = []

    def apply_modifications(self, modifications: List[Tuple[str, int, str, str]]) -> None:
        """Apply modifications to create new structure"""
        # Start with copy of original fields
        self.new_fields = []
        processed_offsets = set()

        # Process modifications
        for field_name, array_index, new_type, new_name in modifications:
            # Find the original field
            original_field = None
            for field in self.original.fields:
                if field.name == field_name:
                    original_field = field
                    break

            if not original_field:
                print(f"Warning: Field '{field_name}' not found in original struct")
                continue

            # Calculate actual offset
            if array_index is not None:
                actual_offset = original_field.offset + array_index
            else:
                actual_offset = original_field.offset

            # Calculate size of new field
            new_size = self._calculate_field_size(new_type)

            # Create new field
            new_field = Field(
                offset=actual_offset,
                name=new_name,
                type_str=new_type,
                size=new_size,
                comment=f"Modified from {field_name}" + (f"[{array_index}]" if array_index else "")
            )

            self.new_fields.append(new_field)
            processed_offsets.add(actual_offset)

        # Now process original fields, splitting arrays as needed
        for field in self.original.fields:
            if field.is_array and field.is_gap:
                # Process gap arrays specially - they might need to be split
                self._process_gap_array(field, processed_offsets)
            elif field.offset not in processed_offsets:
                # Keep original field as-is
                self.new_fields.append(field)

        # Sort fields by offset
        self.new_fields.sort(key=lambda f: f.offset)

        # Merge adjacent gaps
        self._merge_adjacent_gaps()

    def _calculate_field_size(self, type_str: str) -> int:
        """Calculate field size based on type string"""
        if 'void *' in type_str or '*' in type_str:
            return 4
        elif '__int32' in type_str:
            return 4
        elif '__int16' in type_str:
            return 2
        else:
            return 1

    def _process_gap_array(self, gap_field: Field, processed_offsets: set) -> None:
        """Split gap array around modified fields"""
        gap_start = gap_field.offset
        gap_end = gap_field.offset + gap_field.size

        # Find all modified fields within this gap
        modifications_in_gap = []
        for new_field in self.new_fields:
            if gap_start <= new_field.offset < gap_end:
                modifications_in_gap.append(new_field)

        if not modifications_in_gap:
            # No modifications in this gap, keep it as-is
            self.new_fields.append(gap_field)
            return

        # Sort modifications by offset
        modifications_in_gap.sort(key=lambda f: f.offset)

        # Create new gap fields around modifications
        current_offset = gap_start

        for mod_field in modifications_in_gap:
            # Add gap before modification if needed
            if mod_field.offset > current_offset:
                gap_size = mod_field.offset - current_offset
                new_gap = Field(
                    offset=current_offset,
                    name=f"gap_{current_offset:04X}",
                    type_str="unsigned __int8",
                    size=gap_size,
                    is_gap=True,
                    is_array=True,
                    array_size=gap_size
                )
                self.new_fields.append(new_gap)

            current_offset = mod_field.offset + mod_field.size

        # Add remaining gap after last modification
        if current_offset < gap_end:
            gap_size = gap_end - current_offset
            new_gap = Field(
                offset=current_offset,
                name=f"gap_{current_offset:04X}",
                type_str="unsigned __int8",
                size=gap_size,
                is_gap=True,
                is_array=True,
                array_size=gap_size
            )
            self.new_fields.append(new_gap)

    def _merge_adjacent_gaps(self) -> None:
        """Merge adjacent gap fields"""
        merged_fields = []
        i = 0

        while i < len(self.new_fields):
            field = self.new_fields[i]

            if field.is_gap and i + 1 < len(self.new_fields):
                next_field = self.new_fields[i + 1]

                # Check if next field is adjacent gap
                if (next_field.is_gap and
                        field.offset + field.size == next_field.offset):
                    # Merge gaps
                    merged_size = field.size + next_field.size
                    merged_gap = Field(
                        offset=field.offset,
                        name=f"gap_{field.offset:04X}",
                        type_str="unsigned __int8",
                        size=merged_size,
                        is_gap=True,
                        is_array=True,
                        array_size=merged_size
                    )
                    merged_fields.append(merged_gap)
                    i += 2  # Skip next field
                    continue

            merged_fields.append(field)
            i += 1

        self.new_fields = merged_fields

    def generate_output(self) -> str:
        """Generate the modified structure definition"""
        output = []
        output.append(
            f"{self.original.struct_name} struct {self.original.struct_name} // sizeof=0x{self.original.struct_size:X}")
        output.append("{")

        current_offset = 0

        for field in self.new_fields:
            # Add padding if needed
            if field.offset > current_offset:
                gap_size = field.offset - current_offset
                output.append(f"    unsigned __int8 gap_{current_offset:04X}[{gap_size}];")

            # Format field
            if field.is_array:
                output.append(f"    {field.type_str} {field.name}[{field.array_size}]; // {field.comment}")
            else:
                output.append(f"    {field.type_str} {field.name}; // {field.comment}")

            current_offset = field.offset + field.size

        # Add final padding if needed
        if current_offset < self.original.struct_size:
            gap_size = self.original.struct_size - current_offset
            output.append(f"    unsigned __int8 gap_{current_offset:04X}[{gap_size}];")

        output.append("};")

        return '\n'.join(output)


def main():
    if len(sys.argv) < 3:
        print("Usage: python struct_modifier.py <struct_file> <modifications_file>")
        sys.exit(1)

    struct_file = sys.argv[1]
    mods_file = sys.argv[2]

    # Read files
    try:
        with open(struct_file, 'r') as f:
            struct_content = f.read()

        with open(mods_file, 'r') as f:
            mods_content = f.read()
    except FileNotFoundError as e:
        print(f"Error: {e}")
        sys.exit(1)

    # Parse original structure
    parser = StructParser()
    parser.parse_struct(struct_content)
    print(f"Parsed structure: {parser.struct_name} (size: 0x{parser.struct_size:X})")
    print(f"Found {len(parser.fields)} fields")

    # Parse modifications
    mod_parser = ModificationParser()
    mod_parser.parse_modifications(mods_content)
    print(f"Found {len(mod_parser.modifications)} modifications")

    # Apply modifications
    modifier = StructModifier(parser)
    modifier.apply_modifications(mod_parser.modifications)

    # Generate output
    output = modifier.generate_output()
    print("\n=== Modified Structure ===")
    print(output)

    # Optionally save to file
    if len(sys.argv) > 3:
        output_file = sys.argv[3]
        with open(output_file, 'w') as f:
            f.write(output)
        print(f"\nSaved to: {output_file}")


if __name__ == "__main__":
    main()
