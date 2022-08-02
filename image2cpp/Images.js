// Filetypes accepted by the file picker
const fileTypes = ["jpg", "jpeg", "png", "bmp", "gif", "svg"];

// An images collection with helper methods
class Images {
  constructor() {
    this.collection = [];
  }
  push(img, canvas, glyph) {
    this.collection.push({ img, canvas, glyph });
  }
  remove(image) {
    let i = this.collection.indexOf(image);
    if (i != -1) this.collection.splice(i, 1);
  }
  each(f) {
    this.collection.forEach(f);
  }
  length() {
    return this.collection.length;
  }
  first() {
    return this.collection[0];
  }
  last() {
    return this.collection[this.collection.length - 1];
  }
  getByIndex(index) {
    return this.collection[index];
  }
  setByIndex(index, img) {
    this.collection[index] = img;
  }
  get(img) {
    if (img) {
      for (let i = 0; i < this.collection.length; i++) {
        if (this.collection[i].img == img) {
          return this.collection[i];
        }
      }
    }
    return this.collection;
  }
}

exports.Images = Images;
exports.fileTypes = fileTypes;
