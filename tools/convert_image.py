from PIL import Image
import numpy as np
# Load the image
img_path = '/home/gliese/project/creditcard_showoff/creditcard_cv_showoff/img/helloworld.png'
img = Image.open(img_path)

# convert the image to binary (1 bit per pixel) using dithering
bw_img = img.convert('1', dither=Image.NONE)


# Resize the image to 128x32 pixels (if necessary)

bw_img = bw_img.resize((128, 32), Image.Resampling.LANCZOS)
bw_img.show()


# Initialize a buffer to store the bytes
byte_buffer = bytearray()

# each byte corresponds to a coulmn of 8 pixels
# so we need to iterate over the image in chunks of 8 pixels
for y in range(0,4):
    for x in range(0,128):
        byte = 0x00
        # iterate over the 8 bits in the byte
        for i in range(0,8):
            # get the pixel value (0 or 255)
            bit = bw_img.getpixel((x, y*8+i))
            # threshold to 0 or 1
            bit = 0 if bit < 128 else 1
            # reverse the value (0 is black, 1 is white)
            bit = 1 - bit
            # set the i-th bit in the byte
            byte |= bit << i
        # add the byte to the buffer
        byte_buffer.append(byte)

print("len(byte_buffer):", len(byte_buffer))
# format the byte buffer as a hexadecimal string
formatted_hex_str = ', '.join([f"0x{byte:02X}" for byte in byte_buffer])

# Optionally, print or save the hexadecimal buffer to a file
#print("{" + formatted_hex_str + "};")

# print the hexadecimal buffer in a nice format (16 bytes per line)
print("{")
for i in range(0, len(byte_buffer), 16):
    print(", ".join([f"0x{byte:02X}" for byte in byte_buffer[i:i+16]]) + ",")
   
   
print("};")

