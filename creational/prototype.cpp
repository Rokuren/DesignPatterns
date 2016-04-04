/**
 * PROTOTYPE
 *  The factory knows how to find the correct Prototype, and each Product knows how to spawn 
 *    new instances of iteslf.
 *  "new" operator not used, in it's place are calls to the clone method.
 *  Factory method identifies correty prototype object and calls factory method
 *  Maintains a "registry" of prototypical objects.
 *  Creation through delegation
 *  Although this examples usage of new in the clone seems incorrect.
 *    Should maybe use new if no prototype exists than actually clone
 *    the prototype object. Copy Constructor.
 */
#include <iostream.h>

enum imageType {
	LSAT, SPOT	
};

class Image {
	public:
		virtual void draw() = 0;
		static Image *findAndClone(imageType);
	protected:
		virtual imageType returnType() = 0;
    // The method that's used to replace new operations
		virtual Image *clone() = 0;
		// As each subclass of Image is declared, it registers its prototype
		static void addPrototype(Image *image) {
			_prototypes[_nextSlot++] = image;
		}
	private:
    // addPrototype() saves each registered prototype here
    static Image *_prototypes[10];
    static int _nextSlot;
};

Image *Image::_prototypes[];
int Image::_nextSlot;

// Client calls this public static member function when it needs an instance
//  of an Image subclass
Image *Image::findAndClone(imageType type) {
  for(int i = 0; i < _nextSlot; i++) {
    if(_prototypes[i]->returnType() == type) {
      return _prototypes[i]->clone();
    }
  }
}

class LandSatImage: public Image {
  public:
    imageType returnType() {
      return LSAT;
    }
    void draw() {
      cout << "LandSatImage::draw " << _id << endl;
    }
    // When clone() is called, call the one-argument ctor with a dummy arg
    Image *clone() {
      return new LandSatImage(1);
    }
  protected:
    // This only called from clone()
    LandSatImage(int dummy) {
      _id = _count++;
    }
  private:
    // Mechanism for initializing an Image subclass - this causes the
    //  default actor to be called, which registers the subclass's prototype
    static LandSatImage _landSatImage;
    // This is only Called when the private static data member is inited 
    LandSatImage() {
      addPrototype(this);
    }
    // Nominal "state" per instance mechanism
    int _id;
    static int _count;
};

// Register the subclass's prototype
LandSatImage LandSatImage::_landSatImage;
// Initialze the "state" per instance mechanism
int LandSatImage::_count = 1;

class SpotImage: public Image {
  public:
    imageType returnType() {
      return SPOT;
    }
    void draw() {
      cout << "SpotImage::draw " << _id << endl;
    }
    Image *clone() {
      return new SpotImage(1);
    }
  protected:
    SpotImage(int dummy) {
      _id = _count++;
    }
  private:
    SpotImage() {
      addPrototype(this);
    }
    static SpotImage _spotImage;
    int _id;
    static int _count;
};

SpotImage SpotImage::_spotImage;
int SpotImage::_count = 1;

// Simulated stream of creation requests
const int NUM_IMAGES = 8;
imageType input[NUM_IMAGES] = { LSAT, LSAT, LSAT, SPOT, LSAT, SPOT, SPOT, LSAT };

int main() {
  Image *images[NUM_IMAGES];

  // Given an image type, find the right prototype, and return a clone
  for(int i = 0; i < NUM_IMAGES; i++) {
    images[i] = Image::findAndClone(input[i]);
  }

  // Demonstrate that correct image objects have been cloned
  for(i = 0; i < NUM_IMAGES; i++) {
    images[i]->draw();
  }

  // Free the dynamic memory
  for(i = 0; i < NUM_IMAGES; i++) {
    delete images[i];
  }
}