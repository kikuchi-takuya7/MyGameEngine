#include "Quad.h"

class Dice : public Quad 
{
public:
	Dice();
	~Dice();
	virtual void MakeVerBf() override;
};