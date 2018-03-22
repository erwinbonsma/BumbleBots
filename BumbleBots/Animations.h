
//-----------------------------------------------------------------------------
// Animation declaration

class Animation {
  uint8_t _clock;

protected:
  uint8_t clock() const { return _clock; }
  void rewindClock() { _clock--; }

public:
  virtual Animation* init();

  /* Updates the animations.
   *
   * Returns the next animation to use. Can be itself (to continue the current
   * animation), an other one (to move to a new phase), or 0 to signal that the
   * animation is finished.
   */
  virtual Animation* update();

  virtual void draw() {};
};

//-----------------------------------------------------------------------------
// DieAnimation declaration

class DieAnimation : public Animation {
  const char *_cause;

public:
  Animation* init(const char *cause);

  Animation* update();

  void draw();
};

//-----------------------------------------------------------------------------
// GameOverAnimation declaration

class GameOverAnimation : public Animation {

public:
  Animation* init();

  Animation* update();

  void draw();
};

//-----------------------------------------------------------------------------
// LevelDoneAnimation declaration

class LevelDoneAnimation : public Animation {
public:
  Animation* init();

  Animation* update();
};

//-----------------------------------------------------------------------------
// LevelStartAnimation declaration

class LevelStartAnimation : public Animation {
public:
  Animation* init();

  Animation* update();
};
