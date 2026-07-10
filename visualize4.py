import json
import PIL.Image
import PIL.ImageDraw


def create_font_sheet(json_file, output_image="font4_sheet.png"):
    """Create a visual font sheet from the JSON dump"""

    with open(json_file, 'r', encoding='utf-8') as f:
        font_data = json.load(f)

    # Calculate image size
    glyphs_per_row = 16
    cell_size = 50
    padding = 2

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
        half_width = int(width / 2)

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

        # Draw character info
        char_str = glyph["char"] if len(glyph["char"]) == 1 else f"{glyph['char_code']:02X}"
        draw.text((x_base, y_base + height + 2), char_str, fill='blue')

    img.save(output_image)
    print(f"Font sheet saved to {output_image}")


# Usage
if __name__ == "__main__":
    create_font_sheet("font4.json")
