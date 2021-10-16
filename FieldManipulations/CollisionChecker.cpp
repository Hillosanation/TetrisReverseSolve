#include "CollisionChecker.h"
#include "..\Misc\CommonFunctions.h"

bool CollisionChecker::test(std::vector<std::vector<bool>> input, int i, int j) {
	return (!InRange(i, 0, input.size() - 1) or !InRange(j, 0, input[0].size() - 1));
} //a test of the condition in FillOutOfBounds

bool CollisionChecker::FillOutOfBounds(TPlayFieldFilled current, int x, int y, bool FillBool) {
	int CurWidth = current.size();
	int CurHeight = current[0].size(); //takes advantage of current being rectangular

	if (!InRange(x, 0, CurWidth - 1) or !InRange(y, 0, CurHeight - 1)) {
		return FillBool;
	}
	else {
		return current[x][y];
	};
}


CollisionChecker::CollisionChecker() {};

bool CollisionChecker::HaveCollision(TPlayFieldFilled a, TPlayFieldFilled b) { //expects two std::vector<std::vector<bool>>,  checks collision (assume size equal and boxed)
	bool collide = false;
	int width = a.size();
	int length = a[0].size();

	/*for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			std::cout << a[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			std::cout << b[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			std::cout << (a[i][j] and b[i][j]);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;*/
	/*std::vector<TPlayFieldFilled> fields = { a, b };
	std::cout << "Collision Check: " << std::endl;
	DebugPrintPlayFields(fields);
	std::cout << std::endl;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			std::cout << (a[i][j] and b[i][j]);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;*/

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (a[i][j] and b[i][j]) { //check for collision
				collide = true;
				return collide; //collision, end search
			}
		}
	}
	return collide;
}

bool CollisionChecker::HaveCollisionPartial(std::vector<std::vector<bool>> a, std::vector<std::vector<bool>> b, bool FillBool) { //more general, but may be more costly
	int MaxWidth = std::max(a.size(), b.size()); //takes advantage that both are rectangular fields
	int MaxHeight = std::max(a[0].size(), b[0].size());

	bool collide = false;

	/*for (int i = 0; i < MaxWidth; i++) {
		for (int j = 0; j < MaxHeight; j++) {
			std::cout << FillOutOfBounds(a, i, j, FillBool);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < MaxWidth; i++) {
		for (int j = 0; j < MaxHeight; j++) {
			std::cout << FillOutOfBounds(b, i, j, FillBool);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < MaxWidth; i++) {
		for (int j = 0; j < MaxHeight; j++) {
			std::cout << (FillOutOfBounds(a, i, j, FillBool) and FillOutOfBounds(b, i, j, FillBool));
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;*/

	for (int i = 0; i < MaxWidth; i++) {
		for (int j = 0; j < MaxHeight; j++) {
			if (FillOutOfBounds(a, i, j, FillBool) and FillOutOfBounds(b, i, j, FillBool)) { //check for collision
				collide = true;
				return collide; //collision, end search
			}
		}
	}

	return collide;

}
