CREATE DATABASE  IF NOT EXISTS `alegria` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `alegria`;
-- MySQL dump 10.13  Distrib 5.5.40, for debian-linux-gnu (x86_64)
--
-- Host: 192.168.56.2    Database: alegria
-- ------------------------------------------------------
-- Server version	5.1.73

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `product_family`
--

DROP TABLE IF EXISTS `product_family`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `product_family` (
  `idproduct_family` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `image` varchar(300) NOT NULL,
  `active` tinyint(1) NOT NULL,
  `reg_date` datetime NOT NULL,
  PRIMARY KEY (`idproduct_family`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `product_family`
--

LOCK TABLES `product_family` WRITE;
/*!40000 ALTER TABLE `product_family` DISABLE KEYS */;
INSERT INTO `product_family` VALUES (1,'refreshments','refresh.jpg',1,'2014-12-14 13:31:19'),(2,'liquors','liquors.jpg',1,'2014-12-14 13:34:23'),(3,'beers','beers.jpg',1,'2014-12-14 13:34:23'),(4,'wines','wines.jpg',1,'2014-12-14 13:34:23'),(5,'patxaranak','patxaranak.jpg',1,'2014-12-14 13:34:23');
/*!40000 ALTER TABLE `product_family` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `product_item`
--

DROP TABLE IF EXISTS `product_item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `product_item` (
  `idproduct_item` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(200) NOT NULL,
  `image` varchar(300) NOT NULL,
  `active` tinyint(1) NOT NULL,
  `reg_date` datetime NOT NULL,
  `idproduct_family` int(11) NOT NULL,
  PRIMARY KEY (`idproduct_item`),
  KEY `fk_product_item_product_family_idx` (`idproduct_family`),
  CONSTRAINT `fk_product_item_product_family` FOREIGN KEY (`idproduct_family`) REFERENCES `product_family` (`idproduct_family`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `product_item`
--

LOCK TABLES `product_item` WRITE;
/*!40000 ALTER TABLE `product_item` DISABLE KEYS */;
INSERT INTO `product_item` VALUES (1,'water','water.jpg',1,'2014-12-14 13:38:57',1),(2,'coke','coke.jpg',1,'2014-12-14 13:38:57',1),(3,'licor43','licor43.jpg',1,'2014-12-14 13:38:57',2),(4,'orujo','orujo.jpg',1,'2014-12-14 13:38:57',2),(5,'franziskaner','franziskaner.jpg',1,'2014-12-14 13:38:57',3),(6,'naparbier','naparbier.jpg',1,'2014-12-14 13:38:57',3);
/*!40000 ALTER TABLE `product_item` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-12-14 13:49:10
