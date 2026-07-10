import json
import PIL.Image
import PIL.ImageDraw


def create_font_sheet(json_file, output_image=None):
    """Create a visual font sheet from the JSON dump"""

    if output_image is None:
        output_image = json_file.replace('.json', '_sheet.png')

    with open(json_file, 'r', encoding='utf-8') as f:
        font_data = json.load(f)

    # Calculate image size
    glyphs_per_row = 16
    cell_size = 80  # Increased to accommodate larger glyphs
    padding = 4

    num_glyphs = len(font_data["glyphs"])
    rows = (num_glyphs + glyphs_per_row - 1) // glyphs_per_row

    img_width = glyphs_per_row * cell_size
    img_height = rows * cell_size

    # Create image
    img = PIL.Image.new('RGB', (img_width, img_height), 'white')
    draw = PIL.ImageDraw.Draw(img)

    for idx, glyph in enumerate(font_data["glyphs"]):
        row = idx // glyphs_per_row
        col = idx % glyphs_per_row

        x_base = col * cell_size + padding
        y_base = row * cell_size + padding

        # Draw bitmap
        bitmap_data = glyph["bitmap_data"]
        width = glyph["width"]
        height = glyph["height"]

        # Handle different font types
        if "half_width" in glyph:
            # Table-based font (styles 1-3)
            half_width = glyph["half_width"]
            render_table_based_glyph(draw, bitmap_data, width, height, half_width, x_base, y_base)
        else:
            # Hardcoded font (styles 4-5) - assume 1bpp packed format
            render_packed_bitmap_glyph(draw, bitmap_data, width, height, x_base, y_base)

        # Draw character info
        char_str = glyph["char"] if len(glyph["char"]) == 1 else f"{glyph['char_code']:02X}"

        # Add size info for hardcoded fonts
        info_text = char_str
        if "metric" in glyph:
            info_text += f" M:{glyph['metric']}"
        if width > 30 or height > 30:  # For large glyphs, show dimensions
            info_text += f" {width}x{height}"

        draw.text((x_base, y_base + min(height, cell_size - 20) + 2), info_text, fill='blue')

        # Draw cell border
        draw.rectangle([x_base - 1, y_base - 1, x_base + min(width, cell_size - padding) + 1,
                        y_base + min(height, cell_size - padding) + 1], outline='lightgray')

    img.save(output_image)
    print(f"Font sheet saved to {output_image}")


def render_table_based_glyph(draw, bitmap_data, width, height, half_width, x_base, y_base):
    """Render glyph from table-based font (original format)"""
    byte_idx = 0
    for y in range(height):
        x = 0
        for byte_x in range(half_width):
            if byte_idx >= len(bitmap_data):
                break

            byte = bitmap_data[byte_idx]
            for bit in range(2):
                if x >= width:
                    break
                if byte & (0x80 >> bit * 4):
                    draw.point((x_base + x, y_base + y), fill='black')
                x += 1
            byte_idx += 1


def render_packed_bitmap_glyph(draw, bitmap_data, width, height, x_base, y_base):
    """Render glyph from hardcoded font (1bpp packed bitmap)"""
    byte_idx = 0
    bit_pos = 0

    for y in range(height):
        for x in range(width):
            if byte_idx >= len(bitmap_data):
                break

            # Get current bit
            byte = bitmap_data[byte_idx]
            pixel = (byte >> (7 - bit_pos)) & 1

            if pixel:
                draw.point((x_base + x, y_base + y), fill='black')

            # Move to next bit
            bit_pos += 4
            if bit_pos >= 8:
                bit_pos = 0
                byte_idx += 1


def render_multi_bpp_glyph(draw, bitmap_data, width, height, x_base, y_base, bpp=2):
    """Render glyph with multiple bits per pixel (for antialiased fonts)"""
    byte_idx = 0
    bit_pos = 0

    for y in range(height):
        for x in range(width):
            if byte_idx >= len(bitmap_data):
                break

            # Extract pixel value (bpp bits)
            pixel_val = 0
            for bit in range(bpp):
                if byte_idx < len(bitmap_data):
                    byte = bitmap_data[byte_idx]
                    pixel_bit = (byte >> (7 - bit_pos)) & 1
                    pixel_val |= (pixel_bit << (bpp - 1 - bit))

                    bit_pos += 1
                    if bit_pos >= 8:
                        bit_pos = 0
                        byte_idx += 1

            # Convert to grayscale (for antialiasing)
            if bpp == 2:
                gray_levels = [255, 170, 85, 0]  # 4 levels
                color = gray_levels[pixel_val] if pixel_val < len(gray_levels) else 255
            else:
                color = 255 - (pixel_val * 255 // ((1 << bpp) - 1))

            if color < 255:  # Don't draw white pixels
                draw.point((x_base + x, y_base + y), fill=(color, color, color))


def analyze_and_visualize_font(json_file):
    """Analyze font and create visualization with different rendering attempts"""

    with open(json_file, 'r', encoding='utf-8') as f:
        font_data = json.load(f)

    print(f"Analyzing font: {font_data['font_name']}")
    print(f"Font type: {font_data.get('font_type', 'unknown')}")
    print(f"Total glyphs: {font_data['total_glyphs']}")

    # Analyze bitmap sizes to guess encoding
    if font_data['glyphs']:
        sample_glyph = font_data['glyphs'][0]
        width = sample_glyph['width']
        height = sample_glyph['height']
        data_size = len(sample_glyph['bitmap_data'])

        expected_1bpp = (width * height + 7) // 8
        expected_2bpp = (width * height * 2 + 7) // 8
        expected_4bpp = (width * height * 4 + 7) // 8

        print(f"\nBitmap analysis for sample glyph ({width}x{height}):")
        print(f"  Actual data size: {data_size} bytes")
        print(f"  Expected for 1bpp: {expected_1bpp} bytes")
        print(f"  Expected for 2bpp: {expected_2bpp} bytes")
        print(f"  Expected for 4bpp: {expected_4bpp} bytes")

        if data_size == expected_1bpp:
            print("  -> Likely 1bpp format")
        elif data_size == expected_2bpp:
            print("  -> Likely 2bpp format")
        elif data_size == expected_4bpp:
            print("  -> Likely 4bpp format")
        elif "half_width" in sample_glyph:
            print("  -> Table-based format with custom encoding")
        else:
            print("  -> Unknown format")

    # Create visualization
    create_font_sheet(json_file)

    # If it's a hardcoded font with potential different encodings, try alternatives
    if font_data.get('font_type') in ['hardcoded_switch', 'hardcoded_switch_with_metrics']:
        try_alternative_renderings(json_file)


def try_alternative_renderings(json_file):
    """Try different rendering methods for hardcoded fonts"""

    base_name = json_file.replace('.json', '')

    # Try 2bpp rendering
    create_font_sheet_with_custom_renderer(json_file, f"{base_name}_2bpp_sheet.png",
                                           render_method='2bpp')

    # Try different bit ordering
    create_font_sheet_with_custom_renderer(json_file, f"{base_name}_alt_sheet.png",
                                           render_method='alt_bit_order')


def create_font_sheet_with_custom_renderer(json_file, output_image, render_method='1bpp'):
    """Create font sheet with custom rendering method"""

    with open(json_file, 'r', encoding='utf-8') as f:
        font_data = json.load(f)

    # Calculate image size
    glyphs_per_row = 16
    cell_size = 80
    padding = 4

    num_glyphs = len(font_data["glyphs"])
    rows = (num_glyphs + glyphs_per_row - 1) // glyphs_per_row

    img_width = glyphs_per_row * cell_size
    img_height = rows * cell_size

    # Create image
    img = PIL.Image.new('RGB', (img_width, img_height), 'white')
    draw = PIL.ImageDraw.Draw(img)

    for idx, glyph in enumerate(font_data["glyphs"]):
        row = idx // glyphs_per_row
        col = idx % glyphs_per_row

        x_base = col * cell_size + padding
        y_base = row * cell_size + padding

        bitmap_data = glyph["bitmap_data"]
        width = glyph["width"]
        height = glyph["height"]

        if render_method == '2bpp':
            render_multi_bpp_glyph(draw, bitmap_data, width, height, x_base, y_base, 2)
        elif render_method == 'alt_bit_order':
            render_alt_bit_order_glyph(draw, bitmap_data, width, height, x_base, y_base)
        else:
            render_packed_bitmap_glyph(draw, bitmap_data, width, height, x_base, y_base)

        # Draw character info
        char_str = glyph["char"] if len(glyph["char"]) == 1 else f"{glyph['char_code']:02X}"
        draw.text((x_base, y_base + min(height, cell_size - 20) + 2), char_str, fill='blue')

    img.save(output_image)
    print(f"Alternative font sheet ({render_method}) saved to {output_image}")


def render_alt_bit_order_glyph(draw, bitmap_data, width, height, x_base, y_base):
    """Render with alternative bit ordering (LSB first)"""
    byte_idx = 0
    bit_pos = 0

    for y in range(height):
        for x in range(width):
            if byte_idx >= len(bitmap_data):
                break

            # Get current bit (LSB first)
            byte = bitmap_data[byte_idx]
            pixel = (byte >> bit_pos) & 1

            if pixel:
                draw.point((x_base + x, y_base + y), fill='black')

            # Move to next bit
            bit_pos += 1
            if bit_pos >= 8:
                bit_pos = 0
                byte_idx += 1


# Usage
if __name__ == "__main__":
    import sys

    # if len(sys.argv) > 1:
    #     json_file = sys.argv[1]
    # else:
    #     json_file = "font4.json"  # Default
    #
    # analyze_and_visualize_font(json_file)

    # Create sheets for all font files if they exist
    for font_file in ["font1.json", "font2.json", "font3.json", "font4.json", "font5.json"]:
        try:
            create_font_sheet(font_file)
            print(f"Created sheet for {font_file}")
        except FileNotFoundError:
            print(f"File {font_file} not found, skipping")
        except Exception as e:
            print(f"Error processing {font_file}: {e}")
