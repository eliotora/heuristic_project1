# Load files
best.known <- rep(read.csv("~/CLionProjects/heuristic_project1/Best-known Values")$BestKnown, each=5)
ils.results <- read.csv("/home/eliotora/CLionProjects/heuristic_project1/ILS_results/ils_results_time_normal")
ma.results <- read.csv("/home/eliotora/CLionProjects/heuristic_project1/MA_results/ma_results_time_normal")


ils.time <- ils.results$Time
ils.score <- ils.results$TW

ma.score <- ma.results$TW

# Compute percentage deviation for each instance
ils.percentage_deviation <- 100 * (ils.score - best.known) / best.known
ils.percentage_deviation.50 <- ils.percentage_deviation[1:50]
ils.percentage_deviation.100 <- ils.percentage_deviation[51:100]

ma.percentage_deviation <- 100 * (ma.score - best.known) / best.known
ma.percentage_deviation.50 <- ma.percentage_deviation[1:50]
ma.percentage_deviation.100 <- ma.percentage_deviation[51:100]

# Compute average percentage_deviation for each size of instance
ils.average.50 <- sum(ils.percentage_deviation.50)/50
ils.average.100 <- sum(ils.percentage_deviation.100)/50

ma.average.50 <- sum(ma.percentage_deviation.50)/50
ma.average.100 <- sum(ma.percentage_deviation.100)/50

percentage_deviation_instance <- data.frame("Instance", "ILS", "MA")

for(i in 1:20){
  percentage_deviation_instance[i,1] <- ils.results$Instance[i*5] 
  percentage_deviation_instance[i,2] <- sum(ils.percentage_deviation[seq(i*5-4, i*5)])/5
  percentage_deviation_instance[i,3] <- sum(ma.percentage_deviation[seq(i*5-4, i*5)])/5
}
percentage_deviation_instance[,2] <- as.numeric(percentage_deviation_instance[,2])
percentage_deviation_instance[,3] <- as.numeric(percentage_deviation_instance[,3])
percentage_deviation_instance[,3]

percentage_deviation_instance

average_percentage_deviation <- data.frame(InstanceSize = c(50,100),
                                           ILS = c(ils.average.50, ils.average.100),
                                           MA = c(ma.average.50, ma.average.100))
average_percentage_deviation

x <- percentage_deviation_instance[,"X.ILS."]
y <- percentage_deviation_instance[,"X.MA."]

plot(x[11:20], y[11:20], xlim=c(-60,-10), ylim=c(-60,-10), col="red",
     main="Correlation of percentage deviation for instances of size 50 and instances of size 100",
     xlab="Percentage deviation of ILS algorithm",
     ylab="Percentage deviation of MA algorithm")
points(x[1:10], y[1:10], col="blue")
fit <- lm(X.MA. ~ X.ILS., data=percentage_deviation_instance[11:20,])
abline(fit, col="red")
fit <- lm(X.MA. ~ X.ILS., data=percentage_deviation_instance[1:10,])
abline(fit, col="blue")
fit
text(paste("Correlation:", round(cor(x[1:10], y[1:10]), 2)), x = -50, y = -20, col="blue")

text(paste("Correlation:", round(cor(x[11:20], y[11:20]), 2)), x = -50, y = -22, col="red")
legend(x="topleft",
       legend=c("Instance size 50", "Instance size 100"),
       lty = c(1, 1),           # Line types
       col = c("blue", "red"),           # Line colors
       lwd = 2)


wilcox.test (ils.percentage_deviation.50, ma.percentage_deviation.50, paired=T)$p.value
wilcox.test (ils.percentage_deviation.100, ma.percentage_deviation.100, paired=T)$p.value
