kb := splitkb/kyria/rev2
km := wjossowski
config := -kb ${kb} -km ${km}

dir := $(shell pwd)

build: 
	qmk compile ${config}

rebuild: clean images
	qmk compile -c ${config}

install: keymap
	qmk flash ${config}

keymap: build
	qmk c2json ${config} --no-cpp -o ${dir}/out/keymap.json ${dir}/keymap.c

reinstall: rebuild install

aseprite := /Applications/Aseprite.app/Contents/MacOS/aseprite

img_src := ${dir}/gfx
img_export := ${dir}/gfx/images

images_export:
	mkdir -p ${img_export}
	${aseprite} -b ${img_src}/markers.aseprite --all-layers --save-as ${img_export}/markers_{frame}_raw.png
	${aseprite} -b ${img_src}/layers.aseprite --all-layers --save-as ${img_export}/layer_{frame}_raw.png
	${aseprite} -b ${img_src}/templeos_logo.aseprite --all-layers --save-as ${img_export}/templeos_logo_raw.png

images_rotate: images_export
	convert ${img_export}/layer_1_raw.png -rotate 270 ${img_export}/layer_0.png
	convert ${img_export}/layer_2_raw.png -rotate 270 ${img_export}/layer_1.png
	convert ${img_export}/layer_3_raw.png -rotate 270 ${img_export}/layer_2.png
	convert ${img_export}/layer_4_raw.png -rotate 270 ${img_export}/layer_3.png
	convert ${img_export}/layer_5_raw.png -rotate 270 ${img_export}/layer_4.png
	
	convert ${img_export}/templeos_logo_raw.png -rotate 270 ${img_export}/templeos_logo.png
	rm -rf ${img_export}/*.raw.png

images: images_rotate
	node seed.js layer_0 ${img_export}/layer_0.png
	node seed.js layer_1 ${img_export}/layer_1.png
	node seed.js layer_2 ${img_export}/layer_2.png
	node seed.js layer_3 ${img_export}/layer_3.png
	node seed.js layer_4 ${img_export}/layer_4.png
	
#	node seed.js layer_0 ${img_export}/layer_0.png 32 32
#	node seed.js layer_1 ${img_export}/layer_1.png 32 32
#	node seed.js layer_2 ${img_export}/layer_2.png 32 32
# node seed.js layer_3 ${img_export}/layer_3.png 32 32

#	node seed.js markers_0 ${img_export}/markers_0.png 32 32
#	node seed.js markers_1 ${img_export}/markers_1.png 32 32
#	node seed.js markers_2 ${img_export}/markers_2.png 32 32
#	node seed.js markers_3 ${img_export}/markers_3.png 32 32

	node seed.js templeos_logo ${img_export}/templeos_logo.png 128 32

clean:
	rm -rf ${img_export}