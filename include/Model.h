// Copyright 2020 Carmelo Evoli (GSSI) - MIT License

class Model {
   public:
    Model() {}
    virtual ~Model() = default;
    virtual double get(double x, std::vector<double> params) const = 0;
};
