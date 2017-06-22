
float f_offset = 1.0f;
double offset = 42.0;
long double l_offset = 100.0l;

double add_abs(double inputVal=1.0)
{
  if (inputVal >= 0.0) {
    return (inputVal + offset);
  } else {
    return (inputVal - offset);
  }
}
