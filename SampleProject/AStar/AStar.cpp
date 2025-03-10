#include <iostream>
#include "TAstar.h"
//std::bind(함수 주소, 함수인자1, 함수인자2, 함수인자3, ...)
//std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ... 등을 새로운 함수 인자와 맵핑 시킬수있다.
//void Func(int iA, float fB, bool bC);
//auto funcA = std::bind(Func, 10, 2.0f, true);funcA();
//auto funcB = std::bind(Func, 10, std::placeholders::_1, true);funcB(2.0f);
//auto funcC = std::bind(Func, std::placeholders::_2, std::placeholders::_1, true);funcC(2.0f, 10);
//auto funcD = std::bind(Func, std::placeholders::_2, std::placeholders::_1, std::placeholders::_3);funcD(2.0f, 10, true);
//그리고 전역함수가 아닌 클래스 함수의 경우
//&ClassA::FuncA 행태를 바인드의 첫번쩨 인자로 사용한다
using namespace AStar;
int main()
{
    AStar::Generator generator;
	generator.setWorldSize({ 8, 5 });
	generator.addCollision({ 4,0 });
	generator.addCollision({ 4,1 });
	generator.addCollision({ 4,2 });
	generator.addCollision({ 4,3 });
	//generator.addCollision({ 4,4 });

	generator.addCollision({ 1,1 });
	generator.addCollision({ 1,2 });
	generator.addCollision({ 1,3 });
	//generator.addCollision({ 1,4 });

	generator.addCollision({ 2,3 });
	generator.addCollision({ 3,3 });

	generator.setHeuristic(Heuristic::euclidean);
	auto path = generator.findPath({2,2}, {6,2});
    std::cout << "Hello World!\n";
}
