const { createCanvas, loadImage } = require("canvas");
const { Images } = require("./Images");

const fn = async (argv) => {
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
        const avg = (data[index] + data[index + 1] + data[index + 2]) / 3;
        if (avg > settings.threshold) {
          number += Math.pow(2, byteIndex);
        }
        byteIndex--;

        // if this was the last pixel of a row or the last pixel of the
        // image, fill up the rest of our byte with zeros so it always contains 8 bits
        if ((index != 0 && (index / 4 + 1) % canvasWidth == 0) || index == data.length - 4) {
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

      for (let p = 0; p < Math.ceil(settings.screenHeight / 8); p++) {
        for (let x = 0; x < settings.screenWidth; x++) {
          let byteIndex = 7;
          let number = 0;

          for (let y = 7; y >= 0; y--) {
            let index = (p * 8 + y) * (settings.screenWidth * 4) + x * 4;
            let avg = (data[index] + data[index + 1] + data[index + 2]) / 3;
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
        let rgb = ((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | ((b & 0b11111000) >> 3);
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
        if ((index != 0 && (index / 4 + 1) % canvasWidth == 0) || index == data.length - 4) {
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
  }

  // A bunch of settings used when converting
  const settings = {
    screenWidth: argv.screenWidth || 128,
    screenHeight: argv.screenHeight || 64,
    centerHorizontally: argv.centerHorizontally || false,
    centerVertically: argv.centerVertically || false,
    backgroundColor: argv.background || "white",
    scale: argv.scale || "1",
    drawMode: argv.mode || "horizontal",
    threshold: argv.threshold || 128,
    outputFormat: argv.format || "plain",
    invertColors: argv.invertColors || false,
    identifier: argv.name || "myBitmap",
    conversionFunction: ConversionFunctions[argv.mode] || ConversionFunctions.horizontal1bit,
  };

  // The variable to hold our images. Global so we can easily reuse it when the
  // user updates the settings (change canvas size, scale, invert, etc)
  const images = new Images();

  // Make the canvas black and white
  function blackAndWhite(canvas, ctx) {
    const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
    const data = imageData.data;
    for (let i = 0; i < data.length; i += 4) {
      let avg = (data[i] + data[i + 1] + data[i + 2]) / 3;
      avg > settings.threshold ? (avg = 255) : (avg = 0);
      data[i] = avg; // red
      data[i + 1] = avg; // green
      data[i + 2] = avg; // blue
    }
    ctx.putImageData(imageData, 0, 0);
  }

  // Invert the colors of the canvas
  function invert(canvas, ctx) {
    const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
    const data = imageData.data;
    for (let i = 0; i < data.length; i += 4) {
      data[i] = 255 - data[i]; // red
      data[i + 1] = 255 - data[i + 1]; // green
      data[i + 2] = 255 - data[i + 2]; // blue
    }
    ctx.putImageData(imageData, 0, 0);
  }

  // Draw the image onto the canvas, taking into account color and scaling
  function place_image(image) {
    const img = image.img;
    const canvas = image.canvas;
    const ctx = canvas.getContext("2d");
    image.ctx = ctx;

    // Make sure we're using the right canvas size
    // canvas.width = settings.screenWidth || settings.screenWidth;
    // canvas.height = settings.screenHeight || settings.screenWidth;

    // Invert background if needed
    if (settings.backgroundColor == "transparent") {
      ctx.fillStyle = "rgba(0,0,0,0.0)";
      ctx.globalCompositeOperation = "copy";
    } else {
      if (settings.invertColors) {
        settings.backgroundColor == "white" ? (ctx.fillStyle = "black") : (ctx.fillStyle = "white");
      } else {
        ctx.fillStyle = settings.backgroundColor;
      }
      ctx.globalCompositeOperation = "source-over";
    }
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    // Offset used for centering the image when requested
    let offset_x = 0;
    let offset_y = 0;

    switch (settings.scale) {
      case "1": // Original
        if (settings.centerHorizontally) {
          offset_x = Math.round((canvas.width - img.width) / 2);
        }
        if (settings.centerVertically) {
          offset_y = Math.round((canvas.height - img.height) / 2);
        }
        ctx.drawImage(img, 0, 0, img.width, img.height, offset_x, offset_y, img.width, img.height);
        break;
      case "2": // Fit (make as large as possible without changing ratio)
        let horRatio = canvas.width / img.width;
        let verRatio = canvas.height / img.height;
        let useRatio = Math.min(horRatio, verRatio);

        if (settings.centerHorizontally) {
          offset_x = Math.round((canvas.width - img.width * useRatio) / 2);
        }
        if (settings.centerVertically) {
          offset_y = Math.round((canvas.height - img.height * useRatio) / 2);
        }
        ctx.drawImage(
          img,
          0,
          0,
          img.width,
          img.height,
          offset_x,
          offset_y,
          img.width * useRatio,
          img.height * useRatio
        );
        break;
      case "3": // Stretch x+y (make as large as possible without keeping ratio)
        ctx.drawImage(img, 0, 0, img.width, img.height, offset_x, offset_y, canvas.width, canvas.height);
        break;
      case "4": // Stretch x (make as wide as possible)
        offset_x = 0;
        if (settings.centerVertically) {
          Math.round((offset_y = (canvas.height - img.height) / 2));
        }
        ctx.drawImage(img, 0, 0, img.width, img.height, offset_x, offset_y, canvas.width, img.height);
        break;
      case "5": // Stretch y (make as tall as possible)
        if (settings.centerHorizontally) {
          offset_x = Math.round((canvas.width - img.width) / 2);
        }
        offset_y = 0;
        ctx.drawImage(img, 0, 0, img.width, img.height, offset_x, offset_y, img.width, canvas.height);
        break;
    }
    // Make sure the image is black and white
    if (
      settings.conversionFunction == ConversionFunctions.horizontal1bit ||
      settings.conversionFunction == ConversionFunctions.vertical1bit
    ) {
      blackAndWhite(canvas, ctx);
      if (settings.invertColors) {
        invert(canvas, ctx);
      }
    }
  }

  // Handle selecting an image with the file picker
  async function handleImageSelection(input) {
    const img = await loadImage(input);

    settings.screenWidth = settings.screenWidth ?? img.width;
    settings.screenHeight = settings.screenHeight ?? img.height;
    console.log(`file resolution: ${img.width} x ${img.height}`);
    console.log(`canvas size: ${settings.screenWidth} x ${settings.screenHeight}`);

    const canvas = createCanvas(settings.screenWidth, settings.screenHeight);
    images.push(img, canvas, input.split(".")[0]);
    place_image(images.last());
  }

  function imageToString(image) {
    // extract raw image data
    const ctx = image.ctx;
    const canvas = image.canvas;

    const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
    const data = imageData.data;
    return settings.conversionFunction(data, canvas.width, canvas.height);
  }

  // Get the custom arduino output variable name, if any
  function getIdentifier() {
    return settings.identifier;
  }

  // Output the image string to the textfield
  function outputString() {
    let output_string = "",
      count = 1;
    let code = "";

    switch (settings.outputFormat) {
      case "arduino": {
        images.each(function (image) {
          code = imageToString(image);

          // Trim whitespace from end and remove trailing comma
          code = code.replace(/,\s*$/, "");

          code = "\t" + code.split("\n").join("\n\t") + "\n";
          let variableCount = images.length() > 1 ? count++ : "";
          let comment = "// '" + image.glyph + "', " + image.canvas.width + "x" + image.canvas.height + "px\n";

          code =
            comment +
            "const " +
            getType() +
            " " +
            getIdentifier() +
            variableCount +
            " [] PROGMEM = {" +
            "\n" +
            code +
            "};\n";

          output_string += code;
        });
        break;
      }

      case "arduino_single": {
        let comment = "";
        images.each(function (image) {
          code = imageToString(image);
          code = "\t" + code.split("\n").join("\n\t") + "\n";
          comment = "\t// '" + image.glyph + ", " + image.canvas.width + "x" + image.canvas.height + "px\n";
          output_string += comment + code;
        });

        output_string = output_string.replace(/,\s*$/, "");

        output_string =
          "const " + getType() + " " + +getIdentifier() + " [] PROGMEM = {" + "\n" + output_string + "\n};";
        break;
      }

      case "adafruit_gfx": {
        // bitmap
        let comment = "";
        let useGlyphs = 0;
        images.each(function (image) {
          code = imageToString(image);
          code = "\t" + code.split("\n").join("\n\t") + "\n";
          // comment =
          //     "\t// '" +
          //     image.glyph +
          //     ", " +
          //     image.canvas.width +
          //     "x" +
          //     image.canvas.height +
          //     "px\n";
          output_string += comment + code;
          if (image.glyph.length == 1) useGlyphs++;
        });

        output_string = output_string.replace(/,\s*$/, "");
        output_string =
          "const unsigned char " +
          getIdentifier() +
          "Bitmap" +
          " [] PROGMEM = {" +
          "\n" +
          output_string +
          "\n};\n\n" +
          "const GFXbitmapGlyph " +
          getIdentifier() +
          "Glyphs [] PROGMEM = {\n";

        let firstAschiiChar = 48; // TODO: make this configuratble //document.getElementById("first-ascii-char").value;
        let xAdvance = 0; // TODO: make this configurable //parseInt(document.getElementById("x-advance").value);
        let offset = 0;
        code = "";

        // GFXbitmapGlyph
        images.each(function (image) {
          code +=
            "\t{ " +
            offset +
            ", " +
            image.canvas.width +
            ", " +
            image.canvas.height +
            ", " +
            xAdvance +
            ", " +
            "'" +
            (images.length() == useGlyphs ? image.glyph : String.fromCharCode(firstAschiiChar++)) +
            "'" +
            " }";
          if (image != images.last()) {
            code += ",";
          }
          code += "// '" + image.glyph + "'\n";
          offset += image.canvas.width;
        });
        code += "};\n";
        output_string += code;

        // GFXbitmapFont
        output_string +=
          "\nconst GFXbitmapFont " +
          getIdentifier() +
          "Font PROGMEM = {\n" +
          "\t(uint8_t *)" +
          getIdentifier() +
          "Bitmap,\n" +
          "\t(GFXbitmapGlyph *)" +
          getIdentifier() +
          "Glyphs,\n" +
          "\t" +
          images.length() +
          "\n};\n";
        break;
      }
      default: {
        // plain
        images.each(function (image) {
          code = imageToString(image);
          let comment = "";
          // let comment = !image.glyph // TODO: make configurable flag
          //     ? "// '" +
          //       image.glyph +
          //       "', " +
          //       image.canvas.width +
          //       "x" +
          //       image.canvas.height +
          //       "px\n"
          //     : "";
          if (image.img != images.first().img) comment = "\n" + comment;
          code = comment + code;
          output_string += code;
        });
        // Trim whitespace from end and remove trailing comma
        output_string = output_string.replace(/,\s*$/g, "");
      }
    }

    return output_string;
  }

  function adjust(width, height) {
    settings.screenWidth = width;
    settings.screenHeight = height;
  }

  // get the type (in arduino code) of the output image
  // this is a bit of a hack, it's better to make this a property of the conversion function (should probably turn it into objects)
  function getType() {
    if (settings.conversionFunction == ConversionFunctions.horizontal565) {
      return "uint16_t";
    } else if (settings.conversionFunction == ConversionFunctions.horizontal888) {
      return "unsigned long";
    } else {
      return "unsigned char";
    }
  }

  return { handleImageSelection, outputString, adjust };
};

module.exports = fn;
