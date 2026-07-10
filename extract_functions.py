#!/usr/bin/env python3
"""
Extract function names from Zephyr source code and generate C arrays
for comprehensive function inclusion in signature generation.
Automatically detects headers and functions without hardcoding.
"""

import os
import re
import sys
from pathlib import Path
from collections import defaultdict

def find_function_declarations(file_path):
    """Extract function declarations from C/C++ files."""
    functions = []
    includes = set()
    
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
            
        # Extract includes
        include_pattern = r'#include\s*[<"](.*?)[>"]'
        file_includes = re.findall(include_pattern, content)
        includes.update(file_includes)
        
        # Remove comments and preprocessor directives (simplified)
        content = re.sub(r'/\*.*?\*/', '', content, flags=re.DOTALL)
        content = re.sub(r'//.*$', '', content, flags=re.MULTILINE)
        
        # Function declaration patterns - more comprehensive
        patterns = [
            # Standard function declarations with return type
            r'\b(?:static\s+)?(?:inline\s+)?(?:extern\s+)?([a-zA-Z_][a-zA-Z0-9_]*(?:\s*\*)*)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^)]*\)\s*(?=\{|;)',
            # Function declarations without explicit return type (like main)
            r'\b(?:static\s+)?(?:inline\s+)?([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^)]*\)\s*\{',
            # Function pointers in structs or typedefs
            r'(?:\w+\s+)?\(\s*\*\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*\)\s*\(',
        ]
        
        for pattern in patterns:
            matches = re.finditer(pattern, content, re.MULTILINE)
            for match in matches:
                # Get the function name (usually the last group)
                func_name = match.groups()[-1]
                
                if func_name and is_valid_function_name(func_name):
                    functions.append(func_name)
    
    except Exception as e:
        print(f"Error processing {file_path}: {e}")
    
    return functions, includes

def is_valid_function_name(name):
    """Check if a name is likely a valid function name."""
    if not name or len(name) < 2:
        return False
    
    # Must be valid C identifier
    if not re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', name):
        return False
    
    # Skip obvious non-functions
    skip_patterns = [
        r'^[A-Z_]+$',  # All caps (likely constants)
        r'^CONFIG_',   # Configuration macros
        r'^DT_',       # Device tree macros
        r'_H$',        # Header guards
        r'_H_$',       # Header guards
        r'^__',        # Compiler internals
        r'_t$',        # Type definitions
        r'^[0-9]',     # Starts with number
    ]
    
    for pattern in skip_patterns:
        if re.match(pattern, name):
            return False
    
    # Skip C keywords
    c_keywords = {
        'if', 'else', 'for', 'while', 'do', 'switch', 'case', 'default',
        'return', 'break', 'continue', 'goto', 'sizeof', 'typeof',
        'struct', 'union', 'enum', 'typedef', 'static', 'extern',
        'const', 'volatile', 'register', 'auto', 'inline'
    }
    
    if name in c_keywords:
        return False
    
    return True

def scan_zephyr_sources(workspace_path):
    """Scan all Zephyr workspace directories for function declarations."""
    function_to_headers = defaultdict(set)  # function -> set of headers
    header_functions = defaultdict(set)     # header -> set of functions
    all_headers = set()
    
    workspace_path = Path(workspace_path)
    if not workspace_path.exists():
        print(f"Workspace path not found: {workspace_path}")
        return {}, set()
    
    # Scan all relevant directories in the workspace
    scan_dirs = []
    
    # Core Zephyr
    zephyr_dir = workspace_path / "zephyr"
    if zephyr_dir.exists():
        scan_dirs.append(("Zephyr Core", zephyr_dir))
    
    # Nordic SDK
    nrf_dir = workspace_path / "nrf"
    if nrf_dir.exists():
        scan_dirs.append(("Nordic SDK", nrf_dir))
    
    # nrfxlib
    nrfxlib_dir = workspace_path / "nrfxlib"
    if nrfxlib_dir.exists():
        scan_dirs.append(("Nordic Libraries", nrfxlib_dir))
    
    # HAL modules
    modules_dir = workspace_path / "modules"
    if modules_dir.exists():
        for module_path in modules_dir.iterdir():
            if module_path.is_dir():
                scan_dirs.append((f"Module: {module_path.name}", module_path))
    
    # Bootloader
    bootloader_dir = workspace_path / "bootloader"
    if bootloader_dir.exists():
        scan_dirs.append(("Bootloader", bootloader_dir))
    
    print(f"Scanning workspace: {workspace_path}")
    print(f"Found {len(scan_dirs)} directories to scan:")
    for name, path in scan_dirs:
        print(f"  - {name}: {path}")
    
    # Process each directory
    for dir_name, scan_path in scan_dirs:
        print(f"\nProcessing {dir_name}...")
        
        # Find all header files
        header_files = []
        for header_path in scan_path.rglob('*.h'):
            if header_path.is_file():
                # Convert to relative path from workspace root
                try:
                    rel_path = header_path.relative_to(workspace_path)
                except ValueError:
                    # If path is not relative to workspace, use relative to scan_path
                    rel_path = header_path.relative_to(scan_path)
                
                # Skip internal/private headers
                if any(part.startswith('_') or part.startswith('.') for part in rel_path.parts):
                    continue
                    
                header_files.append((header_path, str(rel_path)))
        
        print(f"  Found {len(header_files)} header files")
        
        # Process header files to extract function declarations
        for header_path, rel_path in header_files:
            functions, includes = find_function_declarations(header_path)
            
            if functions:
                # Normalize header path for inclusion
                include_path = rel_path
                
                # Handle different directory structures
                if rel_path.startswith('zephyr/include/'):
                    include_path = rel_path[15:]  # Remove 'zephyr/include/' prefix
                elif rel_path.startswith('include/'):
                    include_path = rel_path[8:]   # Remove 'include/' prefix
                elif rel_path.startswith('nrf/include/'):
                    include_path = rel_path[12:]  # Remove 'nrf/include/' prefix
                elif '/include/' in rel_path:
                    # Find and remove up to include/
                    parts = rel_path.split('/')
                    if 'include' in parts:
                        idx = parts.index('include')
                        include_path = '/'.join(parts[idx+1:])
                
                all_headers.add(include_path)
                header_functions[include_path].update(functions)
                
                # Map functions to this header
                for func in functions:
                    function_to_headers[func].add(include_path)
        
        # Also scan source files to find additional functions
        source_files = []
        for ext in ['*.c', '*.cpp']:
            for source_path in scan_path.rglob(ext):
                if source_path.is_file():
                    source_files.append(source_path)
        
        print(f"  Found {len(source_files)} source files")
        
        for source_path in source_files:
            functions, includes = find_function_declarations(source_path)
            
            if functions:
                # Try to find corresponding header
                header_path = source_path.with_suffix('.h')
                if header_path.exists():
                    try:
                        rel_header = header_path.relative_to(workspace_path)
                    except ValueError:
                        rel_header = header_path.relative_to(scan_path)
                    
                    include_path = str(rel_header)
                    
                    # Normalize include path
                    if include_path.startswith('zephyr/include/'):
                        include_path = include_path[15:]
                    elif include_path.startswith('include/'):
                        include_path = include_path[8:]
                    elif include_path.startswith('nrf/include/'):
                        include_path = include_path[12:]
                    elif '/include/' in include_path:
                        parts = include_path.split('/')
                        if 'include' in parts:
                            idx = parts.index('include')
                            include_path = '/'.join(parts[idx+1:])
                    
                    all_headers.add(include_path)
                    header_functions[include_path].update(functions)
                    
                    for func in functions:
                        function_to_headers[func].add(include_path)
    
    return header_functions, all_headers

def generate_function_array(header_functions, all_headers, output_file):
    """Generate C code with function arrays and includes."""
    
    with open(output_file, 'w') as f:
        f.write("// Auto-generated function inclusion file\n")
        f.write("// Generated by extract_functions.py\n")
        f.write("// Automatically detected headers and functions\n\n")
        
        # Write all discovered includes
        f.write("// Automatically discovered headers\n")
        sorted_headers = sorted(all_headers)
        for header in sorted_headers:
            # Only include headers that seem to be public API
            if (not header.startswith('arch/') and 
                not header.startswith('drivers/') and
                not 'internal' in header.lower() and
                not 'private' in header.lower()):
                f.write(f"#include <{header}>\n")
        
        f.write("\n// Standard library headers\n")
        std_headers = ['string.h', 'stdio.h', 'stdlib.h', 'math.h', 'stdint.h', 'stdbool.h']
        for header in std_headers:
            f.write(f"#include <{header}>\n")
        
        f.write("\n")
        
        # Collect all unique functions
        all_functions = set()
        for functions in header_functions.values():
            all_functions.update(functions)
        
        # Filter and sort functions
        valid_functions = sorted([f for f in all_functions if is_valid_function_name(f)])
        
        print(f"Found {len(valid_functions)} valid functions")
        
        # Generate function pointer array
        f.write("// Comprehensive function pointer table\n")
        f.write("// Contains all discovered functions from Zephyr headers\n")
        f.write("__attribute__((used, section(\".keep_functions\")))\n")
        f.write("static const void* auto_discovered_function_table[] = {\n")
        
        # Write functions in groups of 10 for readability
        for i, func in enumerate(valid_functions):
            if i % 10 == 0:
                f.write("    // Functions {}-{}\n".format(i, min(i+9, len(valid_functions)-1)))
            
            f.write(f"    {func},\n")
        
        f.write("    NULL  // Sentinel\n")
        f.write("};\n\n")
        
        # Generate function to reference the table
        f.write("// Function to force inclusion of all discovered functions\n")
        f.write("__attribute__((used, noinline))\n")
        f.write("static void force_auto_discovered_functions(void) {\n")
        f.write("    volatile const void **table = (volatile const void **)auto_discovered_function_table;\n")
        f.write("    volatile int count = 0;\n")
        f.write("    \n")
        f.write("    // Count functions in table (forces linker to keep them)\n")
        f.write("    while (table[count] != NULL) {\n")
        f.write("        count++;\n")
        f.write("    }\n")
        f.write("    \n")
        f.write("    // Prevent optimization\n")
        f.write("    (void)count;\n")
        f.write("}\n\n")
        
        # Generate summary comment
        f.write(f"// Summary: {len(valid_functions)} functions from {len(all_headers)} headers\n")
        f.write("// To use: call force_auto_discovered_functions() in your main function\n")

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 extract_functions.py <workspace_path>")
        print("Example: python3 extract_functions.py /Users/freedomcoder/zephyr_sigwork_v2.5.1")
        sys.exit(1)
    
    workspace_path = sys.argv[1]
    output_file = "auto_functions.h"
    
    print("Extracting functions from all workspace modules and libraries...")
    header_functions, all_headers = scan_zephyr_sources(workspace_path)
    
    if not header_functions:
        print("No functions found. Check the Zephyr path.")
        sys.exit(1)
    
    print(f"Generating function array in {output_file}...")
    generate_function_array(header_functions, all_headers, output_file)
    
    print(f"Done! Generated {output_file} with auto-discovered functions and headers.")
    print(f"Found {sum(len(funcs) for funcs in header_functions.values())} total function declarations")
    print(f"From {len(all_headers)} header files")

if __name__ == "__main__":
    main()