tei.file <- "~/CLionProjects/heuristic_project1/VNDResults/--vdn--first--tei--srz"
tie.file <- "~/CLionProjects/heuristic_project1/VNDResults/--vdn--first--tie--srz"

best.known <- rep(read.csv("~/CLionProjects/heuristic_project1/Best-known Values")$BestKnown, each=5)

tei <- read.csv(tei.file)
tei.cost <- tei$TW
tei.cost <- 100 * (tei.cost - best.known) / best.known
tei.cost50 <- tei.cost[1:50]
tei.cost100 <- tei.cost[51:100]
tei.average50 <- sum(tei.cost50)/50
tei.average100 <- sum(tei.cost100)/50

tie <- read.csv(tie.file)
tie.cost <- tie$TW
tie.cost <- 100 * (tie.cost - best.known) / best.known
tie.cost50 <- tie.cost[1:50]
tie.cost100 <- tie.cost[51:100]
tie.average50 <- sum(tie.cost50)/50
tie.average100 <- sum(tie.cost100)/50

tei.time <- tei$Time
tie.time <- tie$Time
tei.time50avg <- sum(tei.time[1:50])
tei.time100avg <- sum(tei.time[51:100])
tie.time50avg <- sum(tie.time[1:50])
tie.time100avg <- sum(tie.time[51:100])

tei.average50
tie.average50
tei.average100
tie.average100

tei.time50avg
tie.time50avg
tei.time100avg
tie.time100avg


#VND vs single neighbourhood
vnd.file <- "~/CLionProjects/heuristic_project1/VNDResults/--vdn--first--tei--srz"
ii.file <- "~/CLionProjects/heuristic_project1/IterativeImprovementResults/--ii--first--transpose--srz"

best.known <- rep(read.csv("~/CLionProjects/heuristic_project1/Best-known Values")$BestKnown, each=5)

vnd <- read.csv(vnd.file)
vnd.cost <- vnd$TW
vnd.cost <- 100 * (vnd.cost - best.known) / best.known
vnd.cost50 <- vnd.cost[1:50]
vnd.cost100 <- vnd.cost[51:100]
vnd.average50 <- sum(vnd.cost50)/50
vnd.average100 <- sum(vnd.cost100)/50

ii <- read.csv(ii.file)
ii.cost <- ii$TW
ii.cost <- 100 * (ii.cost - best.known) / best.known
ii.cost50 <- ii.cost[1:50]
ii.cost100 <- ii.cost[51:100]
ii.average50 <- sum(ii.cost50)/50
ii.average100 <- sum(ii.cost100)/50

vnd.time <- vnd$Time
ii.time <- ii$Time
vnd.time50avg <- sum(vnd.time[1:50])
vnd.time100avg <- sum(vnd.time[51:100])
ii.time50avg <- sum(ii.time[1:50])
ii.time100avg <- sum(ii.time[51:100])

ii.average50 - vnd.average50
ii.average100 - vnd.average100
