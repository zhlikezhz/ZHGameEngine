#pragma once

class Example
{
public:
	virtual void DoInit() = 0;
	virtual void DoUpdate() = 0;
	virtual void DoDestory() = 0;

protected:
	Example() {};
};