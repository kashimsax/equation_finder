#ifndef CHROMOSOME_HH_
#define CHROMOSOME_HH_

#include <cstdint>
#include <bitset>
#include <utility>

#include "./Gene.hh"
#include "./GenesDatabase.hh"

class Chromosome
{
public:

  static constexpr int SIZE = 9;
  static constexpr double CROSSOVER_RATE = 0.7;
  static constexpr double MUTATION_RATE = 0.1;

  typedef std::bitset<SIZE * GENE_SIZE> chrome;

  Chromosome() : _chromosome(0) {}
  // add a gene at index index
  bool addGene(Gene gene, int index);
  // check if the chromosome is of the good shape
  double computeValue() const;
  // generate a new chromosome
  static std::pair<Chromosome *, Chromosome *>
  reproduce(const Chromosome *c1, const Chromosome *c2);
  // mutate the chromosome
  void mutate();
  // print chromosome
  void print() const;
  // print well formated equation
  void prettyPrint() const;
  // get the chromosome
  chrome get() const;
  // set the chromosome
  void set(chrome c);

private:
  Gene getGene(int index);
  chrome _chromosome;
  GenesDatabase _db;
};

#endif