#include "Quad.h"

class Dice : public Quad 
{
public:
	Dice();
	~Dice();
	virtual void SetVartices() override;
	virtual void SetIndex() override;
};