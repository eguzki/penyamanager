CREATE DATABASE  IF NOT EXISTS `alegria` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `alegria`;
-- MySQL dump 10.13  Distrib 5.5.40, for debian-linux-gnu (x86_64)
--
-- Host: 192.168.56.2    Database: alegria
-- ------------------------------------------------------
-- Server version	5.1.71-log

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
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `account` (
  `idaccount` int(11) NOT NULL AUTO_INCREMENT,
  `idmember` int(11) NOT NULL,
  `amount` decimal(10,2) NOT NULL,
  `date` datetime NOT NULL,
  `balance` decimal(10,2) NOT NULL,
  `description` varchar(100) NOT NULL,
  PRIMARY KEY (`idaccount`),
  KEY `fk_account_member1_idx` (`idmember`),
  CONSTRAINT `fk_account_member1` FOREIGN KEY (`idmember`) REFERENCES `member` (`idmember`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (1,1,76.54,'2014-12-01 00:00:00',76.54,'deposit'),(2,1,-54.50,'2014-12-01 00:00:01',22.04,'invoice id: 1'),(3,2,20.00,'2014-12-01 00:00:01',20.00,'deposit');
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `inv_prod`
--

DROP TABLE IF EXISTS `inv_prod`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `inv_prod` (
  `idinvoice` int(11) NOT NULL,
  `idproduct_item` int(11) NOT NULL,
  `count` int(11) NOT NULL,
  PRIMARY KEY (`idinvoice`,`idproduct_item`),
  KEY `fk_invoice_has_product_item_product_item1_idx` (`idproduct_item`),
  KEY `fk_invoice_has_product_item_invoice1_idx` (`idinvoice`),
  CONSTRAINT `fk_invoice_has_product_item_invoice1` FOREIGN KEY (`idinvoice`) REFERENCES `invoice` (`idinvoice`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_invoice_has_product_item_product_item1` FOREIGN KEY (`idproduct_item`) REFERENCES `product_item` (`idproduct_item`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `inv_prod`
--

LOCK TABLES `inv_prod` WRITE;
/*!40000 ALTER TABLE `inv_prod` DISABLE KEYS */;
INSERT INTO `inv_prod` VALUES (1,1,10),(1,2,10),(1,5,7),(2,5,1);
/*!40000 ALTER TABLE `inv_prod` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `invoice`
--

DROP TABLE IF EXISTS `invoice`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `invoice` (
  `idinvoice` int(11) NOT NULL AUTO_INCREMENT,
  `state` int(11) NOT NULL,
  `date` datetime NOT NULL,
  `total` decimal(10,2) NOT NULL,
  `idmember` int(11) NOT NULL,
  `payment` int(11) NOT NULL,
  PRIMARY KEY (`idinvoice`),
  KEY `fk_invoice_member1_idx` (`idmember`),
  CONSTRAINT `fk_invoice_member1` FOREIGN KEY (`idmember`) REFERENCES `member` (`idmember`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `invoice`
--

LOCK TABLES `invoice` WRITE;
/*!40000 ALTER TABLE `invoice` DISABLE KEYS */;
INSERT INTO `invoice` VALUES (1,2,'2014-12-23 17:11:52',-54.50,1,1),(2,0,'2014-12-23 17:11:52',-3.50,2,1);
/*!40000 ALTER TABLE `invoice` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `member`
--

DROP TABLE IF EXISTS `member`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `member` (
  `idmember` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `surname` varchar(100) NOT NULL,
  `curr_idinvoice` int(11) DEFAULT NULL,
  `image` varchar(300) NOT NULL,
  `lastmodified` datetime NOT NULL,
  `reg_date` datetime NOT NULL,
  PRIMARY KEY (`idmember`),
  KEY `fk_member_invoice1_idx` (`curr_idinvoice`),
  CONSTRAINT `fk_member_invoice1` FOREIGN KEY (`curr_idinvoice`) REFERENCES `invoice` (`idinvoice`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `member`
--

LOCK TABLES `member` WRITE;
/*!40000 ALTER TABLE `member` DISABLE KEYS */;
INSERT INTO `member` VALUES (1,'Eguzki','Astiz Lezaun',NULL,'mypicture.png','2014-12-01 00:00:00','2014-12-01 00:00:00'),(2,'Urko','Usunariz Fernandez',2,'mypicture2.png','2014-12-01 00:00:00','2014-12-01 00:00:00');
/*!40000 ALTER TABLE `member` ENABLE KEYS */;
UNLOCK TABLES;

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
  `price` decimal(10,2) NOT NULL,
  PRIMARY KEY (`idproduct_item`),
  KEY `fk_product_item_product_family_idx` (`idproduct_family`),
  CONSTRAINT `fk_product_item_product_family` FOREIGN KEY (`idproduct_family`) REFERENCES `product_family` (`idproduct_family`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `product_item`
--

LOCK TABLES `product_item` WRITE;
/*!40000 ALTER TABLE `product_item` DISABLE KEYS */;
INSERT INTO `product_item` VALUES (1,'water','water.jpg',1,'2014-12-14 13:38:57',1,1.00),(2,'coke','coke.jpg',1,'2014-12-14 13:38:57',1,2.00),(3,'licor43','licor43.jpg',1,'2014-12-14 13:38:57',2,3.00),(4,'orujo','orujo.jpg',1,'2014-12-14 13:38:57',2,2.50),(5,'franziskaner','franziskaner.jpg',1,'2014-12-14 13:38:57',3,3.50),(6,'naparbier','naparbier.jpg',1,'2014-12-14 13:38:57',3,1.00);
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

-- Dump completed on 2014-12-26 16:00:59
