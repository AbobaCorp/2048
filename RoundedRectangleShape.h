#pragma once
#include <SFML/Graphics/Shape.hpp>
#include <cmath>

namespace sf {
	class RoundedRectangleShape : public sf::Shape
	{
	public:

		explicit RoundedRectangleShape(const sf::Vector2f& size = sf::Vector2f(0, 0), float radius = 0, unsigned int cornerPointCount = 30);

		void setSize(const sf::Vector2f& size);

		const sf::Vector2f& getSize() const;

		void setCornersRadius(float radius);

		float getCornersRadius() const;

		void setCornerPointCount(unsigned int count);

		virtual std::size_t getPointCount() const;

		virtual sf::Vector2f getPoint(std::size_t index) const;

	private:
		sf::Vector2f mySize;
		float myRadius;
		unsigned int myCornerPointCount;
	};
}