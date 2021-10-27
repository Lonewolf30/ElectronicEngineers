#include "./rendering/RenderingEngine.h"

using namespace std;

int main() {

	RenderingEngine renderingEngine = RenderingEngine();
	renderingEngine.LoadScene(new MainMenu());
	renderingEngine.Start();

	return 0;
}

