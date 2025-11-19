#include <valarray>
#include <print>
#include <map>
#include <string>

using state_t = std::valarray<double>;

void fderiv(double t, const state_t  & s, state_t & dsdt, 
            std::map<std::string, double> & p);
void solve_ivp(double t0, double tf, double dt, state_t & s, 
                std::map<std::string, double> & p);

int main(void)
{
    state_t s(2);
    // initial conditions
    s[0] = 1.2345;
    s[1] = 0.0;
    // params
    std::map<std::string, double> params;
    params["W0"] = 2.435;
    params["lambda"] = 7.0;

    state_t dsdt(2);
    solve_ivp(0.0, 10.987765, 0.1, s, params);

    return 0;
}

void fderiv(double t, const state_t  & s, state_t & dsdt, 
            std::map<std::string, double> & p)
{
    dsdt[0] = s[1];
    dsdt[1] = -p["W0"]*p["W0"]*std::pow(s[0], p["lambda"]);
}

void solve_ivp(double t0, double tf, double dt, state_t & s, std::map<std::string, double> & p)
{
    state_t dsdt(s.size()), k1(s.size()), k2(s.size()),k3(s.size()), k4(s.size());
    for(double t = t0; t <= tf; t = t + dt) {
        // fderiv(t, s, dsdt, p);
        // s = s + dt*dsdt;// euler

        // rk4
        fderiv(t, s, dsdt, p);
        k1 = dt*dsdt;
        fderiv(t + dt/2, s + k1/2, dsdt, p);
        k2 = dt*dsdt;
        fderiv(t + dt/2, s + k2/2, dsdt, p);
        k3 = dt*dsdt;
        fderiv(t + dt, s + k3, dsdt, p);
        k4 = dt*dsdt;
        s = s + (k1 + 2*k2 + 2*k3 + k4)/6.0;
        
        // print
        std::println("{} {} {}", t, s[0], s[1]);
    }
}