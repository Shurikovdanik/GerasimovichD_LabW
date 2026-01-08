#pragma once
#include "Number.h"
#include <vector>
#include <stdexcept>
#include <cmath>

namespace Algebra
{

    class Vector
    {
    private:
        std::vector<Numbers::Number> scalars;

    public:
        Vector(Numbers::Number *args, int n)
        {
            scalars.assign(args, args + n);
        }

        Vector(const std::vector<Numbers::Number> &vals) : scalars(vals) {}

        int dimensions() const
        {
            return static_cast<int>(scalars.size());
        }

        Numbers::Number &operator[](int i)
        {
            return scalars[i];
        }
        const Numbers::Number &operator[](int i) const
        {
            return scalars[i];
        }

        Numbers::Number EuclNorma()
        {
            Numbers::Number res = Numbers::Number(0.0f);
            for (int i = 0; i < dimensions(); i++)
            {
                res = res + (scalars[i] * scalars[i]);
            }
            return res.sqrt();
        }

        Numbers::Number dot(const Vector &other)
        {
            if (dimensions() != other.dimensions())
            {
                throw std::invalid_argument("Vectors must have same dimension for dot product");
            }
            Numbers::Number res = Numbers::Number(0.0f);
            for (int i = 0; i < dimensions(); i++)
            {
                res = res + (scalars[i] * other.scalars[i]);
            }
            return res;
        }

        Vector operator+(const Vector &other) const
        {
            if (dimensions() != other.dimensions())
            {
                throw std::invalid_argument("Vectors must have same dimension for addition");
            }
            std::vector<Numbers::Number> result;
            for (int i = 0; i < dimensions(); i++)
            {
                result.push_back(scalars[i] + other.scalars[i]);
            }
            return Vector(result);
        }

        Vector operator-(const Vector &other) const
        {
            if (dimensions() != other.dimensions())
            {
                throw std::invalid_argument("Vectors must have same dimension for subtraction");
            }
            std::vector<Numbers::Number> result;
            for (int i = 0; i < dimensions(); i++)
            {
                result.push_back(scalars[i] - other.scalars[i]);
            }
            return Vector(result);
        }

        Vector operator*(const Numbers::Number &scalar)
        {
            std::vector<Numbers::Number> result;
            for (int i = 0; i < dimensions(); i++)
            {
                result.push_back(scalars[i] * scalar);
            }
            return Vector(result);
        }

        std::pair<long double, long double> toPolar() const
        {
            if (dimensions() != 2)
            {
                throw std::invalid_argument("Polar coordinates are defined only for 2D vectors");
            }
            long double x = scalars[0].toFloat();
            long double y = scalars[1].toFloat();

            long double r = std::sqrt(x * x + y * y);
            long double theta = std::atan2(y, x);

            return {r, theta};
        }

        std::tuple<long double, long double, long double> toSpherical() const
        {
            if (dimensions() != 3)
            {
                throw std::invalid_argument("Spherical coordinates are defined only for 3D vectors");
            }
            long double x = scalars[0].toFloat();
            long double y = scalars[1].toFloat();
            long double z = scalars[2].toFloat();

            long double r = std::sqrt(x * x + y * y + z * z);
            long double theta = std::atan2(y, x);
            long double phi = std::acos(z / r);

            return {r, theta, phi};
        }
    };

}
