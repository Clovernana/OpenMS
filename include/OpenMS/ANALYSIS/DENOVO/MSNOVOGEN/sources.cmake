### the directory name
set(directory include/OpenMS/ANALYSIS/DENOVO/MSNOVOGEN)

### list all header files of the directory here
set(sources_list_h
Chromosome.h
GenPool.h
Mater.h
Mutater.h
MSNovoGen.h
Scorer.h
Killer.h
DefaultScorer.h
DefaultMutater.h
DefaultMater.h
DefaultKiller.h
SwappingMutater.h
SubstitutingMutater.h
RandomMutater.h
ScorerCreator.h
KillerCreator.h
MaterCreator.h
Seeder.h
SeederCreator.h
RandomSeeder.h
ResidueServer.h
SequenceTagSeeder.h
InvertingMutater.h
SimpleDecreasingKiller.h
RandomSequenceSeeder.h
Utilities.h
DefaultSeeder.h
DefaultMater.h
SimpleMater.h
RandomMater.h
ZipMater.h
HomologyKiller.h
NormShrAbuScorer.h
HyperScorer.h
GenAlg.h
MutaterCreator.h
)

### add path to the filenames
set(sources_h)
foreach(i ${sources_list_h})
	list(APPEND sources_h ${directory}/${i})
endforeach(i)

### source group definition
source_group("Header Files\\OpenMS\\ANALYSIS\\DENOVO\\MSNOVOGEN" FILES ${sources_h})

set(OpenMS_sources_h ${OpenMS_sources_h} ${sources_h})
