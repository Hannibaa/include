#pragma once
#include <SFML/Graphics.hpp>
#include <numbers>
#include "Types_renamed.h"

const float Pi = 3.1415f;


inline bool Condition(float& var, int max, int min = 0)
{
	return (var < min || var > max);
}

bool isCollid (sf::Shape* b, sf::Shape* g, float a)
{
	float x1 = b->getPosition().x;
	float y1 = b->getPosition().y;
	float x2 = g->getPosition().x;
	float y2 = g->getPosition().y;
	return (fabs(x1 - x2) <= a && fabs(y1 - y2) <= a);
};

template<typename T, typename S>
float dist2(sf::Vector2<T> a, sf::Vector2<S> b) { 
	return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

template<typename T,typename S>
float dist(sf::Vector2<T> a, sf::Vector2<S> b) {
	return std::sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool IsPointInCircle(sf::Vector2i p, sf::CircleShape circle) {
	return dist2<int,float>(p, circle.getPosition() + (sf::Vector2f{ circle.getRadius(), circle.getRadius() })) 
		                    < circle.getRadius() * circle.getRadius();
};

bool IsPointInCircle(sf::Vector2f Point, sf::Vector2f Center, float Radii) {
	return dist2<float, float>(Point, Center) < Radii*Radii;
}

bool condition1(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f fdist)
{
	return fabs(p2.x - p1.x) > fdist.x || fabs(p2.y - p1.y) > fdist.y ;
}

bool condition2(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f fdist)
{
	return fabs(p2.x - p1.x) > fdist.x && fabs(p2.y - p1.y) > fdist.y;
}

bool Is2PointsClose(sf::Vector2f p1, sf::Vector2f p2, float fdist)
{
	return dist2<float, float>(p1, p2) > fdist * fdist;
}

template<typename T>
float Norm2d(const sf::Vector2<T>& n) {
	return std::sqrtf(n.x * n.x + n.y * n.y);
}

template<typename T>
float Norm2d2(sf::Vector2<T> n) {
	return (n.x * n.x + n.y * n.y);
}

fVec2 direction(fVec2 p1, fVec2 p2) {
	return (1.f / Norm2d(p2 - p1)) * (p2 - p1);
}

fVec2 direction(const fVec2& v) {
	return (1.f / Norm2d(v)) * v;
}

fVec2 normal(fVec2 v) {
	std::swap(v.x, v.y);
	v.y = -v.y;

	return (1.f / Norm2d(v)) * v;
}

fVec2 normal1(fVec2 v) {
	std::swap(v.x, v.y);
	v.y = -v.y;

	return v;
}

fVec2 perpendicularTo(fVec2 v) {
	std::swap(v.x, v.y);
	v.y = -v.y;

	return v;
}

template<typename T>
T sign(T x) { if (x != reinterpret_cast<T> (0)) return x / std::abs(x); return reinterpret_cast<T>( 0); }

bool IsPointInSegment2(sf::Vector2f p, sf::Vector2f p1, sf::Vector2f p2) {
	float lambda = Norm2d2<float>(p - p1) / Norm2d2<float>(p2 - p1);
	if (lambda >= 0.f && lambda <= 1.f) return true;
	return false;
}

bool IsPointInSegment(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b) {
	
	f32 lambda1 = (p.x - a.x) / (b.x - a.x);
	f32 lambda2 = (p.y - a.y) / (b.y - a.y);

	/*3if (lambda1 >= 0.f && lambda1 <= 1.f
		&& lambda2 >= 0.f && lambda2 <= 1.f
		&&  lambda1 - lambda2 < 1.f
		&&  lambda1 - lambda2 > 0.f
		) return true;*/

	if (lambda1 == lambda2 ) return true;

	return false;

}

bool IsPointCloseSegment(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b) {
	return true;
}

template<typename T>
T clamp(T x, T _max, T _min = (T)0) {
	return x < _min ? _min : x < _max ? x : _max;
}

inline f32 xProduct(fVec2 v1, fVec2 v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

template<class T>  // T should have methode set and get position and move;
void moveTo(T* shape, sf::Vector2f to, float speed)
{
	sf::Vector2f p = shape->getPosition();
	static auto p0 = p;
	sf::Vector2f N = (to - p0) / Norm2d<float>(to - p0);
	if (IsPointInSegment(p, p0, to)) {
		shape->move(speed * N);
	}
}