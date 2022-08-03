aseprite := /Applications/Aseprite.app/Contents/MacOS/aseprite

images: 
	mkdir -p images
	${aseprite} -b projects/layers.aseprite --all-layers --save-as images/layer_{frame}.raw.png
	${aseprite} -b projects/templeos_logo.aseprite --all-layers --save-as images/templeos_logo_{frame}.raw.png

	convert images/layer_0.raw.png -rotate 270 images/layer_0.png
	convert images/layer_1.raw.png -rotate 270 images/layer_1.png
	convert images/layer_2.raw.png -rotate 270 images/layer_2.png
	convert images/layer_3.raw.png -rotate 270 images/layer_3.png
	convert images/templeos_logo_0.raw.png -rotate 270 images/templeos_logo_0.png
	rm -rf images/*.raw.png

	node ./seed.js layer_0 images/layer_0.png
	node ./seed.js layer_1 images/layer_1.png
	node ./seed.js layer_2 images/layer_2.png
	node ./seed.js layer_3 images/layer_3.png
	node ./seed.js templeos_logo_0 images/templeos_logo_0.png

clean:
	rm -rf images
