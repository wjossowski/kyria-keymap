const fs = require("fs");
const path = require("path");
const { convert } = require("./image2cpp");

const template = path.join(__dirname, "templates", "gfx.h.template");

const [, , tag, input, width, height] = process.argv;

if (!tag) {
  throw new Error("Image tag (#define TAG) not specified (1st argument)");
}

if (!input) {
  throw new Error("Image path not specified (2nd argument)");
}

run();

async function run() {
  const contents = await convert({
    format: "plain",
    mode: "vertical1bit",
    input,
    screenWidth: width ? +width : 128,
    screenHeight: height ? +height * 2 : 64,
    backgroundColor: "black",
    scale: "3",
  });
  const compiled = fs
    .readFileSync(template, "utf-8")
    .replace(/\${TAG}/, tag.toUpperCase())
    .replace(/\${DATE}/, new Date().toISOString())
    .replace(/\${CONTENTS}/, adjust(contents));

  fs.writeFileSync(path.join(__dirname, `${tag.toLowerCase()}.h`), compiled);
}

function adjust(contents) {
  return contents
    .split("\n")
    .map((line) => `${line} \\`)
    .join("\n");
}
