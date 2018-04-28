/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

//-----------------------------------------------------------------------------
// Animation declaration

class Animation {
  uint8_t _clock;

protected:
  uint8_t clock() const { return _clock; }
  void rewindClock() { _clock--; }
  void setClock(uint8_t value) { _clock = value; }

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
  bool _hiScore;

public:
  Animation* init(bool hiScore);

  Animation* update();

  void draw();
};

//-----------------------------------------------------------------------------
// GameDoneAnimation declaration

class GameDoneAnimation : public Animation {

public:
  Animation* init();

  Animation* update();

  void draw();
};

//-----------------------------------------------------------------------------
// LevelDoneAnimation declaration

class LevelDoneAnimation : public Animation {
  bool _levelHi;

public:
  Animation* init();

  Animation* update();

  void draw();
};

//-----------------------------------------------------------------------------
// LevelStartAnimation declaration

class LevelStartAnimation : public Animation {
public:
  Animation* init();

  Animation* update();
};
