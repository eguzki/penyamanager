SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

DROP SCHEMA IF EXISTS `alegria` ;
CREATE SCHEMA IF NOT EXISTS `alegria` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `alegria` ;

-- -----------------------------------------------------
-- Table `alegria`.`product_family`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`product_family` ;

CREATE TABLE IF NOT EXISTS `alegria`.`product_family` (
  `idproduct_family` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NOT NULL,
  `image` VARCHAR(300) NOT NULL,
  `active` TINYINT(1) NOT NULL,
  `reg_date` DATETIME NOT NULL,
  PRIMARY KEY (`idproduct_family`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alegria`.`product_item`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`product_item` ;

CREATE TABLE IF NOT EXISTS `alegria`.`product_item` (
  `idproduct_item` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(200) NOT NULL,
  `image` VARCHAR(300) NOT NULL,
  `active` TINYINT(1) NOT NULL,
  `reg_date` DATETIME NOT NULL,
  `idproduct_family` INT NOT NULL,
  `price` DECIMAL(10,2) NOT NULL,
  PRIMARY KEY (`idproduct_item`),
  INDEX `fk_product_item_product_family_idx` (`idproduct_family` ASC),
  CONSTRAINT `fk_product_item_product_family`
    FOREIGN KEY (`idproduct_family`)
    REFERENCES `alegria`.`product_family` (`idproduct_family`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alegria`.`member`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`member` ;

CREATE TABLE IF NOT EXISTS `alegria`.`member` (
  `idmember` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) BINARY NOT NULL,
  `surname` VARCHAR(100) NOT NULL,
  `image` VARCHAR(300) NOT NULL,
  `lastmodified` DATETIME NOT NULL,
  `reg_date` DATETIME NOT NULL,
  `active` TINYINT(1) NOT NULL,
  PRIMARY KEY (`idmember`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alegria`.`invoice`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`invoice` ;

CREATE TABLE IF NOT EXISTS `alegria`.`invoice` (
  `idinvoice` INT NOT NULL AUTO_INCREMENT,
  `state` INT NOT NULL,
  `date` DATETIME NOT NULL,
  `total` DECIMAL(10,2) NOT NULL,
  `idmember` INT NOT NULL,
  `payment` INT NOT NULL,
  PRIMARY KEY (`idinvoice`),
  INDEX `fk_invoice_member1_idx` (`idmember` ASC),
  CONSTRAINT `fk_invoice_member1`
    FOREIGN KEY (`idmember`)
    REFERENCES `alegria`.`member` (`idmember`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alegria`.`inv_prod`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`inv_prod` ;

CREATE TABLE IF NOT EXISTS `alegria`.`inv_prod` (
  `idinvoice` INT NOT NULL,
  `idproduct_item` INT NOT NULL,
  `count` INT NOT NULL,
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
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alegria`.`account`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`account` ;

CREATE TABLE IF NOT EXISTS `alegria`.`account` (
  `idaccount` INT NOT NULL AUTO_INCREMENT,
  `idmember` INT NOT NULL,
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
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
