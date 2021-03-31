/** @file
 * Contains the basic dimensions for the units. 
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_DIMENSIONS_INCLUDED
#define DH_UNITS_DIMENSIONS_INCLUDED

#include <string>

namespace dh {
namespace units {
namespace dimensions {


struct length {
    static std::string name() {
        return "m";
    }
};

struct time {
    static std::string name() {
        return "s";
    }
};

// basic unit in si is kilogram, but using gram fits better with the library implementation
struct mass {
    static std::string name() {
        return "g";
    }
};

struct electric_current {
    static std::string name() {
        return "A";
    }
};

struct thermodynamic_temperature {
    static std::string name() {
        return "K";
    }
};

struct amount_of_substance {
    static std::string name() {
        return "mol";
    }
};

struct luminous_intensity {
    static std::string name() {
        return "cd";
    }
};

// Non si basic units that should exist as well
struct angle {
    static std::string name() {
        return "rad";
    }
};

struct angle_degree {
    static std::string name() {
        return "°";
    }
};

struct degree_celsius {
    static std::string name() {
        return "°C";
    }
};

struct degree_fahrenheit {
    static std::string name() {
        return "°F";
    }
};

}
}
}

#endif /* DH_UNITS_DIMENSIONS_INCLUDED */
