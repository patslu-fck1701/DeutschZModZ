class DeutschZTools_WeatherService
{
    static bool SetClear(out string message)
    {
        Weather weather = GetGame().GetWeather();
        if (!weather)
        {
            message = "Weather object not available.";
            return false;
        }

        weather.GetOvercast().Set(0.05, 60, 300);
        weather.GetRain().Set(0.0, 20, 120);
        weather.GetFog().Set(0.0, 20, 120);
        message = "Weather set to clear.";
        return true;
    }

    static bool SetRain(out string message)
    {
        Weather weather = GetGame().GetWeather();
        if (!weather)
        {
            message = "Weather object not available.";
            return false;
        }

        weather.GetOvercast().Set(0.85, 60, 300);
        weather.GetRain().Set(0.65, 30, 180);
        weather.GetFog().Set(0.15, 30, 180);
        message = "Weather set to rain.";
        return true;
    }

    static bool SetStorm(out string message)
    {
        Weather weather = GetGame().GetWeather();
        if (!weather)
        {
            message = "Weather object not available.";
            return false;
        }

        weather.GetOvercast().Set(1.0, 30, 300);
        weather.GetRain().Set(1.0, 20, 180);
        weather.GetFog().Set(0.35, 30, 180);
        weather.SetStorm(1.0, 0.85, 45);
        message = "Weather set to storm.";
        return true;
    }

    static bool SetFog(out string message)
    {
        Weather weather = GetGame().GetWeather();
        if (!weather)
        {
            message = "Weather object not available.";
            return false;
        }

        weather.GetOvercast().Set(0.45, 60, 300);
        weather.GetRain().Set(0.0, 20, 120);
        weather.GetFog().Set(0.75, 30, 180);
        message = "Weather set to fog.";
        return true;
    }
}
