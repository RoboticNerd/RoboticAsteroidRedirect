#include "../functions.h"
#include "../orbmech.h"         /* Functions to be tested */
#include "../constants.h"       /* Constants for testing inputs */

// Initializations for testing
extern const double r_orb_jupiter = 7.786e8;          // km wrt sun


// Including these two allows us to write test cases.
#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.cpp"

TEST_CASE("Hyberbolic excess speed is calculated correctly.", "[departure][relative][orbital_mechanics]"){
    // prepatory code here:
    // std::vector<int> vec = {1, 2, 3};
    REQUIRE(hyperbolicExcessSpeed(u_sun, r_orb_earth, r_orb_jupiter) >= 8.7);
    REQUIRE(hyperbolicExcessSpeed(u_sun, r_orb_earth, r_orb_jupiter) <= 8.9);
}

TEST_CASE("Circular orbit velocity is calculated correctly", "[relative][orbital_mechanics]") {
    REQUIRE(circularOrbitSpeed(u_earth, r_earth+300) >= 7.5);
    REQUIRE(circularOrbitSpeed(u_earth, r_earth+300) <= 8.0);
}

TEST_CASE("Eliptic Departure Speed is calculated correctly", "[relative][orbital_mechanics]") {
    REQUIRE(ellipticDepartureSpeed(u_sun, r_orb_earth, r_orb_jupiter) >= 38.4);
    REQUIRE(ellipticDepartureSpeed(u_sun, r_orb_earth, r_orb_jupiter) <= 38.8);
}

TEST_CASE("Departure Speed is calculated correctly", "[deltaV][departure][relative][orbital_mechanics]") {
    REQUIRE(deltaV_Departure(u_earth, u_sun, r_earth+300, r_orb_earth, r_orb_jupiter) >= 6.2);
    REQUIRE(deltaV_Departure(u_earth, u_sun, r_earth+300, r_orb_earth, r_orb_jupiter) <= 6.4);
}
