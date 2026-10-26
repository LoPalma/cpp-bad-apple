import cv2
import numpy as np

WIDTH = 56
HEIGHT = 42
VIDEO_PATH = "bad_apple.mp4"
OUTPUT_TEXT_H = "frames.h"
OUTPUT_PLAYER_H = "frames_data.h"

def compress_rle_row(row_pixels):
    """Compress a single row into B() (black) and W() (white) macros."""
    if len(row_pixels) == 0:
        return ""

    tokens = []
    current_pixel = row_pixels[0]
    current_len = 0

    for pixel in row_pixels:
        if pixel == current_pixel:
            current_len += 1
        else:
            macro = "W" if current_pixel == 1 else "B"
            tokens.append(f"{macro}({current_len})")
            current_pixel = pixel
            current_len = 1

    macro = "W" if current_pixel == 1 else "B"
    tokens.append(f"{macro}({current_len})")
    return " ".join(tokens)

def write_recursive_ifs(f, start, end, frame_blocks):
    if start == end:
        f.write(f"// Frame {start}\n")
        for row in frame_blocks[start]:
            f.write(f"{row}\n")
        return

    mid = (start + end) // 2
    f.write(f"#if FRAME_NUM <= {mid}\n")
    write_recursive_ifs(f, start, mid, frame_blocks)
    f.write("#else\n")
    write_recursive_ifs(f, mid + 1, end, frame_blocks)
    f.write("#endif\n")

def player_row(row):
    return row.replace("B(", "BA_B(").replace("W(", "BA_W(")

def write_player_header(f, frame_blocks):
    f.write("// Automatically generated - Bad Apple compact frame database 56x42\n\n")
    f.write("#define BA_GLUE(a, b) a ## b\n")
    f.write("#define BA_B(num) BA_GLUE(BA_B_, num)\n")
    f.write("#define BA_W(num) BA_GLUE(BA_W_, num)\n\n")

    for length in range(1, WIDTH + 1):
        f.write(f'#define BA_B_{length} "{("." * length)}"\n')
    f.write("\n")
    for length in range(1, WIDTH + 1):
        f.write(f'#define BA_W_{length} "{("#" * length)}"\n')
    f.write("\n")

    f.write(f"#define TOTAL_FRAMES {len(frame_blocks)}\n\n")
    f.write("static const char *const bad_apple_frames[TOTAL_FRAMES] = {\n")
    for index, rows in enumerate(frame_blocks):
        f.write(f"  // Frame {index}\n")
        parts = [f'{player_row(row)} "\\n"' for row in rows]
        f.write("  " + " ".join(parts) + ",\n")
    f.write("};\n")

def main():
    cap = cv2.VideoCapture(VIDEO_PATH)
    if not cap.isOpened():
        print(f"Error: could not open video {VIDEO_PATH}")
        return

    frame_blocks = []
    frame_count = 0
    print("Processing video...")

    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        resized = cv2.resize(gray, (WIDTH, HEIGHT), interpolation=cv2.INTER_AREA)

        _, thresh = cv2.threshold(resized, 127, 255, cv2.THRESH_BINARY)
        pixels = (thresh > 0).astype(int)

        current_frame_rows = []
        for y in range(HEIGHT):
            row_str = compress_rle_row(pixels[y])
            current_frame_rows.append(row_str)

        frame_blocks.append(current_frame_rows)
        frame_count += 1

    cap.release()
    print(f"Extracted {frame_count} frames. Writing {OUTPUT_TEXT_H} and {OUTPUT_PLAYER_H}...")

    with open(OUTPUT_TEXT_H, "w", encoding="utf-8") as f:
        f.write("// Automatically generated - Bad Apple RLE database 56x42\n\n")
        write_recursive_ifs(f, 0, frame_count - 1, frame_blocks)
        f.write(f"\n#define TOTAL_FRAMES {frame_count}\n")

    with open(OUTPUT_PLAYER_H, "w", encoding="utf-8") as f:
        write_player_header(f, frame_blocks)

    print("Done.")

if __name__ == "__main__":
    main()
