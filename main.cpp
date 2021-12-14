#include <iostream>

// Custom HEADERS
#include "Color.h"
#include "Vec3.h"
#include "Ray.h"

bool hit_sphere(const point3& center, double radius, const Ray& r)
{
    Vec3 oc = r.origin() - center;

    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    return (discriminant > 0);
}

color ray_color(const Ray& r)
{
    if (hit_sphere(point3(0, 0, -1), 0.5, r))
    {
        return color(1, 0, 0);
    }
    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);

    // If t == 1 we get end_value
    // If t == 0 we get start_value
    // The scaling of t is based on the y value of the unit vector
    auto start_value {color(1.0, 1.0, 1.0)};
    auto end_value{color(0.5, 0.7, 1.0)};
    return (1.0-t) * start_value + t * end_value;
}

int main()
{
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height <<"\n255\n";

    for (int j = image_height-1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);

            // Could delete " - origin"
            // If the origin is 0,0,0 then any point on the map is == the vector
            Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
    return 0;
}
