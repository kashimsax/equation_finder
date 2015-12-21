#include "./Population.hh"

Population::Population() :
_winner(NULL), _problem(NULL)
{ }

int Population::solve(Problem *problem) {
    _problem = problem;
    int generation;
    Chromosome *solution;
    generate();
    for (generation = 0; generation < SIMULATION_NUMBER; ++generation)
    {
        if ((solution = test()) != NULL)
            break;
        reproduce();
    }
    if (solution)
    {
        std::cout << "Solution found in " << generation + 1 << " generation(s)" << std::endl;
        _problem->print(solution);
        return true;
    }
    std::cout <<  "Solution not found" << std::endl;
    print();
    return false;
}

void Population::generate()
{
    _problem->askParameters();
    for (int i = 0; i < SIZE; i++)
        _population.push_back(new Chromosome());
}

Chromosome *Population::test()
{
    double fitness;
    _totalFitness = 0;
    for (auto &candidate : _population)
    {   
        if (_problem->test(candidate))
            return candidate;
        fitness = _problem->computeFitnessOf(candidate);
        candidate->setFitness(fitness);
        _totalFitness += candidate->getFitness();
    }
    return NULL;
}

void Population::print() const
{
    for (auto &candidate : _population)
        _problem->print(candidate);
}

Chromosome *Population::selectChromosome() const
{
  double randomNb = std::fmod(std::rand(), _totalFitness);
  double curFitness = 0;
  for (auto &candidate : _population)
  {
    curFitness += candidate->getFitness();
    if (curFitness >= randomNb)
      return candidate;
  }
  // never happen, just here for the compiler
  return NULL;
}

void Population::reproduce()
{
  Generation nextGeneration;
  Chromosome *c1, *c2;
  Chromosome::Children children;
  do
  {
    c1 = selectChromosome();
    c2 = selectChromosome();
    try {
        children = Chromosome::reproduce("one-point", c1, c2);
    } catch (std::string &error) {
        std::cerr << "Crossover " << error << " do not exists" << std::endl;
        break;
    }
    children.first->mutate();
    children.second->mutate();
    nextGeneration.push_back(children.first);
    nextGeneration.push_back(children.second);
  } while (nextGeneration.size() != SIZE);
  clean();
  _population = nextGeneration;
}

void Population::clean()
{
    for (Chromosome *p : _population)
        delete p;
}

Population::~Population()
{
  clean();
}
