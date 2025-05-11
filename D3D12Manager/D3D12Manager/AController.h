#pragma once

class AControlable;

class AController
{
	AController(AControlable& controlable);

protected:
	AControlable& m_controlable;

public:

};