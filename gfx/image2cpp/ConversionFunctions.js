const fn = (settings) =>
    class ConversionFunctions {
        // Output the image as a string for horizontally drawing displays
        static horizontal1bit(data, canvasWidth, canvasHeight) {
            let output_string = "";
            let output_index = 0;

            let byteIndex = 7;
            let number = 0;

            // format is RGBA, so move 4 steps per pixel
            for (let index = 0; index < data.length; index += 4) {
                // Get the average of the RGB (we ignore A)
                const avg =
                    (data[index] + data[index + 1] + data[index + 2]) / 3;
                if (avg > settings.threshold) {
                    number += Math.pow(2, byteIndex);
                }
                byteIndex--;

                // if this was the last pixel of a row or the last pixel of the
                // image, fill up the rest of our byte with zeros so it always contains 8 bits
                if (
                    (index != 0 && (index / 4 + 1) % canvasWidth == 0) ||
                    index == data.length - 4
                ) {
                    // for(let i=byteIndex;i>-1;i--){
                    // number += Math.pow(2, i);
                    // }
                    byteIndex = -1;
                }

                // When we have the complete 8 bits, combine them into a hex value
                if (byteIndex < 0) {
                    let byteSet = number.toString(16);
                    if (byteSet.length == 1) {
                        byteSet = "0" + byteSet;
                    }
                    let b = "0x" + byteSet;
                    output_string += b + ", ";
                    output_index++;
                    if (output_index >= 16) {
                        output_string += "\n";
                        output_index = 0;
                    }
                    number = 0;
                    byteIndex = 7;
                }
            }
            return output_string;
        }

        // Output the image as a string for vertically drawing displays
        static vertical1bit(data, canvasWidth, canvasHeight) {
            let output_string = "";
            let output_index = 0;

            console.log(
                "vertical1bit",
                settings.canvasWidth,
                settings.canvasHeight
            );
            for (let p = 0; p < Math.ceil(settings.canvasHeight / 8); p++) {
                for (let x = 0; x < settings.canvasWidth; x++) {
                    let byteIndex = 7;
                    let number = 0;

                    for (let y = 7; y >= 0; y--) {
                        let index =
                            (p * 8 + y) * (settings.canvasWidth * 4) + x * 4;
                        let avg =
                            (data[index] + data[index + 1] + data[index + 2]) /
                            3;
                        if (avg > settings.threshold) {
                            number += Math.pow(2, byteIndex);
                        }
                        byteIndex--;
                    }
                    let byteSet = number.toString(16);
                    if (byteSet.length == 1) {
                        byteSet = "0" + byteSet;
                    }
                    let b = "0x" + byteSet.toString(16);
                    output_string += b + ", ";
                    output_index++;
                    if (output_index >= 16) {
                        output_string += "\n";
                        output_index = 0;
                    }
                }
            }
            return output_string;
        }

        // Output the image as a string for 565 displays (horizontally)
        static horizontal565(data, canvasWidth, canvasHeight) {
            let output_string = "";
            let output_index = 0;

            // format is RGBA, so move 4 steps per pixel
            for (let index = 0; index < data.length; index += 4) {
                // Get the RGB values
                let r = data[index];
                let g = data[index + 1];
                let b = data[index + 2];
                // calculate the 565 color value
                let rgb =
                    ((r & 0b11111000) << 8) |
                    ((g & 0b11111100) << 3) |
                    ((b & 0b11111000) >> 3);
                // Split up the color value in two bytes
                let firstByte = (rgb >> 8) & 0xff;
                let secondByte = rgb & 0xff;

                let byteSet = rgb.toString(16);
                while (byteSet.length < 4) {
                    byteSet = "0" + byteSet;
                }
                output_string += "0x" + byteSet + ", ";

                // add newlines every 16 bytes
                output_index++;
                if (output_index >= 16) {
                    output_string += "\n";
                    output_index = 0;
                }
            }
            return output_string;
        }
        // Output the image as a string for rgb888 displays (horizontally)
        static horizontal888(data, canvasWidth, canvasHeight) {
            let output_string = "";
            let output_index = 0;

            // format is RGBA, so move 4 steps per pixel
            for (let index = 0; index < data.length; index += 4) {
                // Get the RGB values
                let r = data[index];
                let g = data[index + 1];
                let b = data[index + 2];
                // calculate the 565 color value
                let rgb = (r << 16) | (g << 8) | b;
                // Split up the color value in two bytes
                let firstByte = (rgb >> 8) & 0xff;
                let secondByte = rgb & 0xff;

                const byteSet = rgb.toString(16);
                while (byteSet.length < 8) {
                    byteSet = "0" + byteSet;
                }
                output_string += "0x" + byteSet + ", ";

                // add newlines every 16 bytes
                output_index++;
                if (output_index >= canvasWidth) {
                    output_string += "\n";
                    output_index = 0;
                }
            }
            return output_string;
        }
        // Output the alpha mask as a string for horizontally drawing displays
        static horizontalAlpha(data, canvasWidth, canvasHeight) {
            let output_string = "";
            let output_index = 0;

            let byteIndex = 7;
            let number = 0;

            // format is RGBA, so move 4 steps per pixel
            for (let index = 0; index < data.length; index += 4) {
                // Get alpha part of the image data
                let alpha = data[index + 3];
                if (alpha > settings.threshold) {
                    number += Math.pow(2, byteIndex);
                }
                byteIndex--;

                // if this was the last pixel of a row or the last pixel of the
                // image, fill up the rest of our byte with zeros so it always contains 8 bits
                if (
                    (index != 0 && (index / 4 + 1) % canvasWidth == 0) ||
                    index == data.length - 4
                ) {
                    byteIndex = -1;
                }

                // When we have the complete 8 bits, combine them into a hex value
                if (byteIndex < 0) {
                    let byteSet = number.toString(16);
                    if (byteSet.length == 1) {
                        byteSet = "0" + byteSet;
                    }
                    let b = "0x" + byteSet;
                    output_string += b + ", ";
                    output_index++;
                    if (output_index >= 16) {
                        output_string += "\n";
                        output_index = 0;
                    }
                    number = 0;
                    byteIndex = 7;
                }
            }
            return output_string;
        }
    };

module.exports = fn;
