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

    state_t dsdt(2);
    solve_ivp(0.0, 10.987765, 0.01, s, params);

    return 0;
}

void fderiv(double t, const state_t  & s, state_t & dsdt, 
            std::map<std::string, double> & p)
{
    dsdt[0] = s[1];
    dsdt[1] = -p["W0"]*p["W0"]*s[0];
}

void solve_ivp(double t0, double tf, double dt, state_t & s, std::map<std::string, double> & p)
{
    state_t dsdt(s.size());
    for(double t = t0; t <= tf; t = t + dt) {
        fderiv(t, s, dsdt, p);
        s = s + dt*dsdt;// euler
        std::println("{} {} {}", t, s[0], s[1]);
    }
}