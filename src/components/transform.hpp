// =====================================================================================
//
//       Filename:  transform.hpp
//
//    Description:
//
//        Version:  1.0
//        Created:  06/20/2020 05:41:41 AM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Itziar Morales Rodríguez (IMR), itzimr97@outlook.com
//   Organization:  UTAD
//
// =====================================================================================
#pragma once

#include <glm/glm.hpp>
#include "./component.hpp"

class Transform : public Component
{
private:
	glm::vec2 pos;
	float rot;
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
	~Transform();
};
