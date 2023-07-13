#include "Model.h"
#include "Core/FileIO.h"
#include <sstream>

namespace antares {
	void Model::Draw(Renderer& renderer, const vec2& pos, float rotation, float scale) {
		if (m_points.size() < 2) return;
		for (int i = 0; i < m_points.size()-1; i++) {
			vec2 p1 = (m_points[i] * scale).Rotate(rotation) + pos;
			vec2 p2 = (m_points[i + 1] * scale).Rotate(rotation) + pos;

			renderer.DrawLine(p1.x,p1.y,p2.x,p2.y);
		}
	}

	void Model::Draw(Renderer& renderer, const antares::Transform tf) {
		Draw(renderer, tf.position, tf.rotation, tf.scale);
	}

	

	bool Model::Load(const std::string& filename) {
		std::string buffer;
		antares::readFile(filename, buffer);

		std::istringstream stream(buffer);

		std::string line;
		std::getline(stream, line);

		int numPoints = std::stoi(line);

		for (int i = 0; i < numPoints; i++) {
			Vector2 point;
			stream >> point;
			m_points.push_back(point);
			
		}

		return true;
	}
}