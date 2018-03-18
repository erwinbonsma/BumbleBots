#include <Gamebuino-Meta.h>

#include "Utils.h"

class Object {
  int8_t _objectIndex;

public:
  /* Initialise one-off state.
   */
  virtual void init(int8_t objectIndex);

  /* Invoked each time a level starts.
   */
  virtual void reset() {}

  int8_t index() { return _objectIndex; }

  virtual ObjectType objectType() = 0;

  virtual void visit(int8_t moverIndex) = 0;
  virtual void draw(int8_t x, int8_t y) = 0;
};

class Pickup : public Object {
public:
  ObjectType objectType() { return TYPE_PICKUP; }

  void visit(int8_t moverIndex);
  void draw(int8_t x, int8_t y);
};

