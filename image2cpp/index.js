/*
adjusted from https://gist.githubusercontent.com/taf2/5788459858fb9226a513ac1fedaf6d63/raw/52de5a48a565478ac896624a2e0a9e3750c19d45/converter.js
originally from https://raw.githubusercontent.com/javl/image2cpp/master/index.html
converted from command line interface to package
node converter.js -f arduino -m horizontal1bit -b transparent -n VariableName -i input.bmp -o output.c
head output.c
// 'input', 100x100px
const unsigned char VariableName [] PROGMEM = {
	0x00, 0x00, 0x00

options:
-f : format can be one of plain, arduino, arduino_single, adafruit_gfx
-m : draw mode can be one of  horizontal1bit, vertical1bit, horizontal565, horizontalAlpha, horizontal888
-n : name of output variable
-i : input file .bmp file
-o : output file name e.g. output.c
-b : background color white, black, or transparent
-t : threshold for brightness / alpha threshold
-x : invert colors
*/

// const argv = YArgs.option('format', {
//   alias: 'f',
//   description: 'output format',
//   choices: ['plain', 'arduino', 'arduino_single', 'adafruit_gfx'],
//   type: 'choices',
// }).option('mode', {
//   alias: 'm',
//   description: 'draw mode effects the output byte ranges adjust as needed for your display',
//   choices: ['horizontal1bit', 'vertical1bit', 'horizontal565', 'horizontalAlpha', 'horizontal888'],
//   type: 'choices',
// }).option('name', {
//   alias: 'n',
//   description: 'name of output variable',
//   type: 'string',
// }).option('input', {
//   alias: 'i',
//   description: 'input file .bmp file',
//   type: 'string',
// }).option('output', {
//   alias: 'o',
//   description: 'output file name e.g. output.c',
//   type: 'string',
// }).option('background', {
//   alias: 'b',
//   description: 'background color white, black, or transparent',
//   type: 'string',
// }).option('threshold', {
//   alias: 't',
//   description: 'threshold for brightness / alpha threshold',
//   type: 'number'
// }).option('invert', {
//   alias: 'x',
//   description: 'invert colors',
//   type: 'boolean'
// }).help().alias('help', 'h').argv;

const image2cpp = require("./image2cpp");

exports.convert = async function (argv) {
  const { handleImageSelection, outputString } = await image2cpp(argv);
  await handleImageSelection(argv.input);
  return outputString();
};
