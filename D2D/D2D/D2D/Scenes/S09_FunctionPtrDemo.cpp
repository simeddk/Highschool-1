#include "stdafx.h"
#include "S09_FunctionPtrDemo.h"
#include "Test1.h"
#include "Test2.h"

#define GlobalFuncPtrTest
#define MemberFuncPtrTest
#define FunctionalGlobalTest

void Idle() { ImGui::Text("Idle"); }
void Move() { ImGui::Text("Move"); }
void Attack() { ImGui::Text("Attack"); }
void Progress(void(*callback)())
{
	int progress = (int)(Time::Get()->Running() / 10 * 100);
	progress = Math::Clamp(progress, 0, 100);
	
	ImGui::ProgressBar(Time::Get()->Running() / 10, ImVec2(-1, 0), (to_string(progress) + "%").c_str());

	if (callback != nullptr && progress >= 100)
		callback(); //EventCall
}
void Progress(function<void()> callback)
{
	int progress = (int)(Time::Get()->Running() / 10 * 100);
	progress = Math::Clamp(progress, 0, 100);

	ImGui::ProgressBar(Time::Get()->Running() / 10, ImVec2(-1, 0), (to_string(progress) + "%").c_str());

	if (callback != nullptr && progress >= 100)
		callback();
}
void Reply()
{
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "..Completed!");
}
string MakeRandomBetween(float number1, float number2)
{
	return to_string(Math::Random(number1, number2));
}
string Sum(float val1, float val2)
{
	ImGui::TextColored(ImVec4(1, 0, 0, 1), to_string(val1).c_str());
	ImGui::TextColored(ImVec4(0, 1, 0, 1), to_string(val2).c_str());

	return to_string(val1 + val2);
}

S09_FunctionPtrDemo::S09_FunctionPtrDemo()
{
	
}

S09_FunctionPtrDemo::~S09_FunctionPtrDemo()
{
	
}

void S09_FunctionPtrDemo::Update()
{
#ifndef GlobalFuncPtrTest
	static int behavior;
	ImGui::InputInt("Behavior", &behavior);
	behavior = Math::Clamp(behavior, 0, 2);

	void(*funcPtr[3])() = { Idle, Attack, Move };
	funcPtr[behavior]();

	void(*callback)() = Reply; //Bind
	Progress(callback);

	string(*randomStr)(float n1, float n2);
	randomStr = MakeRandomBetween;
	string result = randomStr(10, 20);
	ImGui::LabelText("Result : ", "%s", result.c_str());

	randomStr = Sum;
	result = randomStr(0.1f, 99.9f);
	ImGui::LabelText("Result : ", "%s", result.c_str());
#endif

#ifndef MemberFuncPtrTest
	//Static(정적) 함수를 저장하는 경우
	void(*funcPtr)();
	funcPtr = &Test1::Start;
	funcPtr();
	
	//비정적 멤버 함수를 저장하는 경우
	Test1 ob;
	void(Test1::*memberPtr)();
	memberPtr = &Test1::Render;
	(ob.*memberPtr)();

	//memberPtr = &Test2::Render;
	//-> functional : 함수포인터를 다루는 STL
#endif

#ifndef FunctionalGlobalTest
	function<void()> voidNoParam;
	voidNoParam = bind(Idle);
	voidNoParam();

	function<string(float, float)> stringTwoParam;
	stringTwoParam = MakeRandomBetween;
	string result = stringTwoParam(17, 20);
	ImGui::Text("%s", result.c_str());

	stringTwoParam = bind(Sum, placeholders::_1, placeholders::_2);
	result = stringTwoParam(100, 999);
	ImGui::Text("%s", result.c_str());
#endif

	function<void()> memberFunc;
	memberFunc = bind(&Test1::Start); //Static
	memberFunc();

	Test1 ob1;
	Test2 ob2;
	memberFunc = bind(&Test1::Render, ob1);
	memberFunc();

	memberFunc = bind(&Test2::Render, ob2);
	memberFunc();

	vector<function<string(float, float)>> events;
	events.push_back(bind(MakeRandomBetween, placeholders::_1, placeholders::_2));
	events.push_back(bind(Sum, placeholders::_1, placeholders::_2));
	events.push_back(bind(&Test1::Mul, ob1, placeholders::_1, placeholders::_2));
	events.push_back(bind(&Test2::Div, ob2, placeholders::_1, placeholders::_2));
	
	ImGui::Separator();
	for (auto e : events)
	{
		string temp = e(800, 200);
		ImGui::Text("%s", temp.c_str());
	}

	Progress(bind(&Test1::Render, ob1));
}

void S09_FunctionPtrDemo::Render()
{
}