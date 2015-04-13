-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
-- -----------------------------------------------------
-- Schema alegriaurko
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `alegriaurko` ;

-- -----------------------------------------------------
-- Schema alegriaurko
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `alegriaurko` DEFAULT CHARACTER SET utf8 ;
-- -----------------------------------------------------
-- Schema alegria
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `alegria` ;

-- -----------------------------------------------------
-- Schema alegria
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `alegria` DEFAULT CHARACTER SET utf8 ;
USE `alegriaurko` ;

-- -----------------------------------------------------
-- Table `alegriaurko`.`member`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegriaurko`.`member` ;

CREATE TABLE IF NOT EXISTS `alegriaurko`.`member` (
  `idmember` INT(11) NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) CHARACTER SET 'utf8' COLLATE 'utf8_bin' NOT NULL,
  `surname` VARCHAR(100) NOT NULL,
  `image` VARCHAR(300) NOT NULL,
  `lastmodified` DATETIME NOT NULL,
  `reg_date` DATETIME NOT NULL,
  `active` TINYINT(1) NOT NULL,
  `isAdmin` TINYINT(1) NOT NULL,
  PRIMARY KEY (`idmember`))
ENGINE = InnoDB
AUTO_INCREMENT = 3
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `alegriaurko`.`account`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegriaurko`.`account` ;

CREATE TABLE IF NOT EXISTS `alegriaurko`.`account` (
  `idaccount` INT(11) NOT NULL AUTO_INCREMENT,
  `idmember` INT(11) NOT NULL,
  `amount` DECIMAL(10,2) NOT NULL,
  `date` DATETIME NOT NULL,
  `balance` DECIMAL(10,2) NOT NULL,
  `description` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`idaccount`),
  INDEX `fk_account_member1_idx` (`idmember` ASC),
  CONSTRAINT `fk_account_member1`
    FOREIGN KEY (`idmember`)
    REFERENCES `alegriaurko`.`member` (`idmember`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 4
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `alegriaurko`.`invoice`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegriaurko`.`invoice` ;

CREATE TABLE IF NOT EXISTS `alegriaurko`.`invoice` (
  `idinvoice` INT(11) NOT NULL AUTO_INCREMENT,
  `state` INT(11) NOT NULL,
  `date` DATETIME NOT NULL,
  `total` DECIMAL(10,2) NOT NULL,
  `idmember` INT(11) NOT NULL,
  `payment` INT(11) NOT NULL,
  PRIMARY KEY (`idinvoice`),
  INDEX `fk_invoice_member1_idx` (`idmember` ASC),
  CONSTRAINT `fk_invoice_member1`
    FOREIGN KEY (`idmember`)
    REFERENCES `alegriaurko`.`member` (`idmember`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 3
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `alegriaurko`.`product_family`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegriaurko`.`product_family` ;

CREATE TABLE IF NOT EXISTS `alegriaurko`.`product_family` (
  `idproduct_family` INT(11) NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NOT NULL,
  `image` VARCHAR(300) NOT NULL,
  `active` TINYINT(1) NOT NULL,
  `reg_date` DATETIME NOT NULL,
  PRIMARY KEY (`idproduct_family`))
ENGINE = InnoDB
AUTO_INCREMENT = 6
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `alegriaurko`.`product_item`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegriaurko`.`product_item` ;

CREATE TABLE IF NOT EXISTS `alegriaurko`.`product_item` (
  `idproduct_item` INT(11) NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(200) NOT NULL,
  `image` VARCHAR(300) NOT NULL,
  `active` TINYINT(1) NOT NULL,
  `reg_date` DATETIME NOT NULL,
  `idproduct_family` INT(11) NOT NULL,
  `price` DECIMAL(10,2) NOT NULL,
  PRIMARY KEY (`idproduct_item`),
  INDEX `fk_product_item_product_family_idx` (`idproduct_family` ASC),
  CONSTRAINT `fk_product_item_product_family`
    FOREIGN KEY (`idproduct_family`)
    REFERENCES `alegriaurko`.`product_family` (`idproduct_family`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 7
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `alegriaurko`.`inv_prod`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegriaurko`.`inv_prod` ;

CREATE TABLE IF NOT EXISTS `alegriaurko`.`inv_prod` (
  `idinvoice` INT(11) NOT NULL,
  `idproduct_item` INT(11) NOT NULL,
  `count` INT(11) NOT NULL,
  PRIMARY KEY (`idinvoice`, `idproduct_item`),
  INDEX `fk_invoice_has_product_item_product_item1_idx` (`idproduct_item` ASC),
  INDEX `fk_invoice_has_product_item_invoice1_idx` (`idinvoice` ASC),
  CONSTRAINT `fk_invoice_has_product_item_invoice1`
    FOREIGN KEY (`idinvoice`)
    REFERENCES `alegriaurko`.`invoice` (`idinvoice`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_invoice_has_product_item_product_item1`
    FOREIGN KEY (`idproduct_item`)
    REFERENCES `alegriaurko`.`product_item` (`idproduct_item`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;

USE `alegria` ;

-- -----------------------------------------------------
-- Table `alegria`.`member`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`member` ;

CREATE TABLE IF NOT EXISTS `alegria`.`member` (
  `idmember` INT(11) NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) CHARACTER SET 'utf8' COLLATE 'utf8_bin' NOT NULL,
  `surname` VARCHAR(100) NOT NULL,
  `image` VARCHAR(300) NOT NULL,
  `lastmodified` DATETIME NOT NULL,
  `reg_date` DATETIME NOT NULL,
  `active` TINYINT(1) NOT NULL,
  `isAdmin` TINYINT(1) NOT NULL DEFAULT '0',
  `birth` DATE NULL DEFAULT NULL,
  `address` VARCHAR(120) NULL DEFAULT NULL,
  `zip_code` INT(11) NULL DEFAULT NULL,
  `town` VARCHAR(45) NULL DEFAULT NULL,
  `state` VARCHAR(45) NULL DEFAULT NULL,
  `tel` INT(11) NULL DEFAULT NULL,
  `tel2` INT(11) NULL DEFAULT NULL,
  `email` VARCHAR(45) NULL DEFAULT NULL,
  `bank_account` VARCHAR(45) NOT NULL,
  `postal_send` TINYINT(1) NULL DEFAULT NULL,
  `notes` VARCHAR(300) NULL DEFAULT NULL,
  PRIMARY KEY (`idmember`))
ENGINE = InnoDB
AUTO_INCREMENT = 3
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `alegria`.`account`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`account` ;

CREATE TABLE IF NOT EXISTS `alegria`.`account` (
  `idaccount` INT(11) NOT NULL AUTO_INCREMENT,
  `idmember` INT(11) NOT NULL,
  `amount` DECIMAL(10,2) NOT NULL,
  `date` DATETIME NOT NULL,
  `balance` DECIMAL(10,2) NOT NULL,
  `description` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`idaccount`),
  INDEX `fk_account_member1_idx` (`idmember` ASC),
  CONSTRAINT `fk_account_member1`
    FOREIGN KEY (`idmember`)
    REFERENCES `alegria`.`member` (`idmember`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 4
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `alegria`.`invoice`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`invoice` ;

CREATE TABLE IF NOT EXISTS `alegria`.`invoice` (
  `idinvoice` INT(11) NOT NULL AUTO_INCREMENT,
  `state` INT(11) NOT NULL,
  `date` DATETIME NOT NULL,
  `total` DECIMAL(10,2) NOT NULL,
  `idmember` INT(11) NOT NULL,
  `payment` INT(11) NOT NULL,
  PRIMARY KEY (`idinvoice`),
  INDEX `fk_invoice_member1_idx` (`idmember` ASC),
  CONSTRAINT `fk_invoice_member1`
    FOREIGN KEY (`idmember`)
    REFERENCES `alegria`.`member` (`idmember`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 3
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `alegria`.`product_family`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`product_family` ;

CREATE TABLE IF NOT EXISTS `alegria`.`product_family` (
  `idproduct_family` INT(11) NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NOT NULL,
  `image` VARCHAR(300) NOT NULL,
  `active` TINYINT(1) NOT NULL,
  `reg_date` DATETIME NOT NULL,
  PRIMARY KEY (`idproduct_family`))
ENGINE = InnoDB
AUTO_INCREMENT = 6
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `alegria`.`product_item`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`product_item` ;

CREATE TABLE IF NOT EXISTS `alegria`.`product_item` (
  `idproduct_item` INT(11) NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(200) NOT NULL,
  `image` VARCHAR(300) NOT NULL,
  `active` TINYINT(1) NOT NULL,
  `reg_date` DATETIME NOT NULL,
  `idproduct_family` INT(11) NOT NULL,
  `price` DECIMAL(10,2) NOT NULL,
  PRIMARY KEY (`idproduct_item`),
  INDEX `fk_product_item_product_family_idx` (`idproduct_family` ASC),
  CONSTRAINT `fk_product_item_product_family`
    FOREIGN KEY (`idproduct_family`)
    REFERENCES `alegria`.`product_family` (`idproduct_family`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 7
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `alegria`.`inv_prod`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`inv_prod` ;

CREATE TABLE IF NOT EXISTS `alegria`.`inv_prod` (
  `idinvoice` INT(11) NOT NULL,
  `idproduct_item` INT(11) NOT NULL,
  `count` INT(11) NOT NULL,
  PRIMARY KEY (`idinvoice`, `idproduct_item`),
  INDEX `fk_invoice_has_product_item_product_item1_idx` (`idproduct_item` ASC),
  INDEX `fk_invoice_has_product_item_invoice1_idx` (`idinvoice` ASC),
  CONSTRAINT `fk_invoice_has_product_item_invoice1`
    FOREIGN KEY (`idinvoice`)
    REFERENCES `alegria`.`invoice` (`idinvoice`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_invoice_has_product_item_product_item1`
    FOREIGN KEY (`idproduct_item`)
    REFERENCES `alegria`.`product_item` (`idproduct_item`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
