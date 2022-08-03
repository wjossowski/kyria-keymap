# Globals
dir := $(shell pwd)
qmk_home := $(shell qmk env | grep QMK_HOME | sed 's/QMK_HOME=//g;s/"//g')
qmk_kyria_dir := ${qmk_home}/keyboards/splitkb/kyria/keymaps

kb := splitkb/kyria/rev2
km := wjossowski
config := -kb ${kb} -km ${km}
# -------------------------------------------------------------------------------- #

# Commands
build: symlink
	qmk compile ${config}

rebuild: symlink clean images
	qmk compile -c ${config}

install: keymap
	qmk flash ${config}

reinstall: rebuild install

keymap: build
	qmk c2json ${config} --no-cpp -o ${dir}/dist/keymap.json ${dir}/keymap.c
	rm -f ${dir}/dist/*.png
	docker-compose up --exit-code-from cypress

# -------------------------------------------------------------------------------- #

# Images Generation
aseprite := /Applications/Aseprite.app/Contents/MacOS/aseprite
img_in := ${dir}/gfx/projects
img_out := ${dir}/gfx/images
images_export:
	mkdir -p ${img_out}
	${aseprite} -b ${img_in}/layers.aseprite --all-layers --save-as ${img_out}/layer_{frame}.raw.png
	${aseprite} -b ${img_in}/templeos_logo.aseprite --all-layers --save-as ${img_out}/templeos_logo_{frame}.raw.png

images_rotate: images_export
	convert ${img_out}/layer_0.raw.png -rotate 270 ${img_out}/layer_0.png
	convert ${img_out}/layer_1.raw.png -rotate 270 ${img_out}/layer_1.png
	convert ${img_out}/layer_2.raw.png -rotate 270 ${img_out}/layer_2.png
	convert ${img_out}/layer_3.raw.png -rotate 270 ${img_out}/layer_3.png
	convert ${img_out}/templeos_logo_0.raw.png -rotate 270 ${img_out}/templeos_logo_0.png
	rm -rf ${img_out}/*.raw.png

images: images_rotate
	node ./gfx/seed.js layer_0 ${img_out}/layer_0.png
	node ./gfx/seed.js layer_1 ${img_out}/layer_1.png
	node ./gfx/seed.js layer_2 ${img_out}/layer_2.png
	node ./gfx/seed.js layer_3 ${img_out}/layer_3.png

	node ./gfx/seed.js templeos_logo_0 ${img_out}/templeos_logo_0.png

clean:
	rm -rf ${img_out}

# -------------------------------------------------------------------------------- #

qmk_rtfm := "Follow these instructions: https://docs.qmk.fm/ to properly set up your environment."
symlink: 
	@echo "Checking the programs required for the build are installed..."
	@echo "Checking if qmk is installed..."
	@(qmk --version >/dev/null 2>&1) || (echo "ERROR: qmk not found. ${qmk_rtfm}"; exit 1)
	@echo "Checking if qmk is properly configured..."
	@(qmk env | grep QMK_HOME >/dev/null 2>&1) || (echo "ERROR: qmk not configured. ${qmk_rtfm}"; exit 1)
	@(qmk env | grep QMK_HOME | sed 's/QMK_HOME=//g;s/"//g' | sed 's/.*/"&"/' >/dev/null 2>&1) || (echo "ERROR: QMK_HOME not configured. ${qmk_rtfm}"; exit 1)
	${shell cd ${qmk_kyria_dir} && ln -s ${dir} ${km}}
