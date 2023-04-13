rand.file <- "~/CLionProjects/heuristic_project1/IterativeImprovementResults/--ii--first--insert--rand"
srz.file <- "~/CLionProjects/heuristic_project1/IterativeImprovementResults/--ii--first--insert--srz"

best.known <- rep(read.csv("~/CLionProjects/heuristic_project1/Best-known Values")$BestKnown, each=5)
rand <- read.csv(rand.file)
rand.cost <- rand$TW
rand.cost <- 100 * (rand.cost - best.known) / best.known
rand.cost50 <- rand.cost[1:50]
rand.cost100 <- rand.cost[51:100]
rand.average50 <- sum(rand.cost50)/50
rand.average100 <- sum(rand.cost100)/50

srz <- read.csv(srz.file)
srz.cost <- srz$TW
srz.cost <- 100 * (srz.cost - best.known) / best.known
srz.cost50 <- srz.cost[1:50]
srz.cost100 <- srz.cost[51:100]
srz.average50 <- sum(srz.cost50)/50
srz.average100 <- sum(srz.cost100)/50

rand.time <- rand$Time
srz.time <- srz$Time
rand.time50avg <- sum(rand.time[1:50])
rand.time100avg <- sum(rand.time[51:100])
srz.time50avg <- sum(srz.time[1:50])
srz.time100avg <- sum(srz.time[51:100])

rand.average50
srz.average50
rand.average100
srz.average100

rand.time50avg
srz.time50avg
rand.time100avg
srz.time100avg

wilcox.test (rand.cost, srz.cost, paired=T)$p.value
