#if !defined(WINDOWS_NEIGHBORS_H)
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct RenderObject
{
	char* name;
	glm::vec2 position;
	glm::vec2 scale;
	glm::vec3 color;
	RenderObject *next;
};

class RenderList
{
	RenderObject *head;

public:
	bool isEmpty = true;
	void Push(RenderObject *obj);

	RenderObject Pop();
};

#define WINDOWS_NEIGHBORS_H
#endif