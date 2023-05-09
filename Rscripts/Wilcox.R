a.cost <- read.csv("~/CLionProjects/heuristic_project1/IterativeImprovementResults/--ii--first--transpose--srz")$TW
b.cost <- read.csv("~/CLionProjects/heuristic_project1/IterativeImprovementResults/--ii--first--insert--srz")$TW
best.known <- rep(read.csv("~/CLionProjects/heuristic_project1/Best-known Values")$BestKnown, each=5)

a.cost <- 100 * (a.cost - best.known) / best.known
b.cost <- 100 * (b.cost - best.known) / best.known

wilcox.test (a.cost, b.cost, paired=T)$p.value