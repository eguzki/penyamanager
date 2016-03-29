-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
-- -----------------------------------------------------
-- Schema alegria
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `alegria` ;

-- -----------------------------------------------------
-- Schema alegria
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `alegria` DEFAULT CHARACTER SET utf8 ;
USE `alegria` ;

-- -----------------------------------------------------
-- Table `alegria`.`member`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`member` ;

CREATE TABLE IF NOT EXISTS `alegria`.`member` (
  `idmember` INT(11) NOT NULL AUTO_INCREMENT COMMENT '',
  `name` VARCHAR(45) CHARACTER SET 'utf8' COLLATE 'utf8_bin' NOT NULL COMMENT '',
  `surname` VARCHAR(100) NOT NULL COMMENT '',
  `image` VARCHAR(300) NULL COMMENT '',
  `lastmodified` DATETIME NOT NULL COMMENT '',
  `reg_date` DATETIME NOT NULL COMMENT '',
  `active` TINYINT(1) NOT NULL COMMENT '',
  `isAdmin` TINYINT(1) NOT NULL COMMENT '',
  `birth` DATE NULL COMMENT '',
  `address` VARCHAR(120) NULL COMMENT '',
  `zip_code` VARCHAR(20) NULL COMMENT '',
  `town` VARCHAR(45) NULL COMMENT '',
  `state` VARCHAR(45) NULL COMMENT '',
  `tel` VARCHAR(45) NULL COMMENT '',
  `tel2` VARCHAR(45) NULL COMMENT '',
  `email` VARCHAR(45) NULL COMMENT '',
  `bank_account` VARCHAR(45) NOT NULL COMMENT '',
  `postal_send` TINYINT(1) NOT NULL COMMENT '',
  `notes` VARCHAR(45) NULL COMMENT '',
  `pwd` VARCHAR(128) NOT NULL COMMENT '',
  `lastlogin` DATETIME NOT NULL COMMENT '',
  PRIMARY KEY (`idmember`)  COMMENT '')
ENGINE = InnoDB
AUTO_INCREMENT = 3
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `alegria`.`account`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`account` ;

CREATE TABLE IF NOT EXISTS `alegria`.`account` (
  `idaccount` INT(11) NOT NULL AUTO_INCREMENT COMMENT '',
  `idmember` INT(11) NOT NULL COMMENT '',
  `amount` DECIMAL(10,2) NOT NULL COMMENT '',
  `date` DATETIME NOT NULL COMMENT '',
  `balance` DECIMAL(10,2) NOT NULL COMMENT '',
  `description` VARCHAR(100) NOT NULL COMMENT '',
  `type` INT(11) NOT NULL COMMENT '',
  PRIMARY KEY (`idaccount`)  COMMENT '',
  INDEX `fk_account_member1_idx` (`idmember` ASC)  COMMENT '',
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
  `idinvoice` INT(11) NOT NULL AUTO_INCREMENT COMMENT '',
  `state` INT(11) NOT NULL COMMENT '',
  `date` DATETIME NOT NULL COMMENT '',
  `total` DECIMAL(10,2) NOT NULL COMMENT '',
  `idmember` INT(11) NOT NULL COMMENT '',
  `last_modif` DATETIME NOT NULL COMMENT '',
  PRIMARY KEY (`idinvoice`)  COMMENT '',
  INDEX `fk_invoice_member1_idx` (`idmember` ASC)  COMMENT '',
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
  `idproduct_family` INT(11) NOT NULL AUTO_INCREMENT COMMENT '',
  `name` VARCHAR(45) NOT NULL COMMENT '',
  `image` VARCHAR(300) NULL COMMENT '',
  `active` TINYINT(1) NOT NULL COMMENT '',
  `reg_date` DATETIME NOT NULL COMMENT '',
  PRIMARY KEY (`idproduct_family`)  COMMENT '')
ENGINE = InnoDB
AUTO_INCREMENT = 6
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `alegria`.`provider`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`provider` ;

CREATE TABLE IF NOT EXISTS `alegria`.`provider` (
  `idprovider` INT NOT NULL AUTO_INCREMENT COMMENT '',
  `name` VARCHAR(200) NOT NULL COMMENT '',
  `image` VARCHAR(200) NULL COMMENT '',
  `reg_date` DATE NULL COMMENT '',
  `phone` VARCHAR(45) NULL COMMENT '',
  PRIMARY KEY (`idprovider`)  COMMENT '')
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alegria`.`product_item`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`product_item` ;

CREATE TABLE IF NOT EXISTS `alegria`.`product_item` (
  `idproduct_item` INT(11) NOT NULL AUTO_INCREMENT COMMENT '',
  `name` VARCHAR(200) NOT NULL COMMENT '',
  `image` VARCHAR(300) NULL COMMENT '',
  `active` TINYINT(1) NOT NULL COMMENT '',
  `reg_date` DATETIME NOT NULL COMMENT '',
  `idproduct_family` INT(11) NOT NULL COMMENT '',
  `price` DECIMAL(10,2) NOT NULL COMMENT '',
  `idprovider` INT(11) NOT NULL COMMENT '',
  `stock` INT(11) NOT NULL COMMENT '',
  PRIMARY KEY (`idproduct_item`)  COMMENT '',
  INDEX `fk_product_item_product_family_idx` (`idproduct_family` ASC)  COMMENT '',
  INDEX `fk_product_item_provider1_idx` (`idprovider` ASC)  COMMENT '',
  CONSTRAINT `fk_product_item_product_family`
    FOREIGN KEY (`idproduct_family`)
    REFERENCES `alegria`.`product_family` (`idproduct_family`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_product_item_provider1`
    FOREIGN KEY (`idprovider`)
    REFERENCES `alegria`.`provider` (`idprovider`)
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
  `idinvoice` INT(11) NOT NULL COMMENT '',
  `idproduct_item` INT(11) NOT NULL COMMENT '',
  `count` INT(11) NOT NULL COMMENT '',
  PRIMARY KEY (`idinvoice`, `idproduct_item`)  COMMENT '',
  INDEX `fk_invoice_has_product_item_product_item1_idx` (`idproduct_item` ASC)  COMMENT '',
  INDEX `fk_invoice_has_product_item_invoice1_idx` (`idinvoice` ASC)  COMMENT '',
  CONSTRAINT `fk_invoice_has_product_item_invoice1`
    FOREIGN KEY (`idinvoice`)
    REFERENCES `alegria`.`invoice` (`idinvoice`)
    ON DELETE CASCADE
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_invoice_has_product_item_product_item1`
    FOREIGN KEY (`idproduct_item`)
    REFERENCES `alegria`.`product_item` (`idproduct_item`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `alegria`.`deposit`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`deposit` ;

CREATE TABLE IF NOT EXISTS `alegria`.`deposit` (
  `iddeposit` INT(11) NOT NULL AUTO_INCREMENT COMMENT '',
  `state` INT(11) NOT NULL COMMENT '',
  `date` DATETIME NOT NULL COMMENT '',
  `total` DECIMAL(10,2) NOT NULL COMMENT '',
  `description` VARCHAR(120) NULL COMMENT '',
  `idmember` INT(11) NOT NULL COMMENT '',
  PRIMARY KEY (`iddeposit`)  COMMENT '',
  INDEX `fk_deposit_member1_idx` (`idmember` ASC)  COMMENT '',
  CONSTRAINT `fk_deposit_member1`
    FOREIGN KEY (`idmember`)
    REFERENCES `alegria`.`member` (`idmember`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 3
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `alegria`.`lunchtables`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`lunchtables` ;

CREATE TABLE IF NOT EXISTS `alegria`.`lunchtables` (
  `idtable` INT(11) NOT NULL COMMENT '',
  `name` VARCHAR(45) NOT NULL COMMENT '',
  `guestnum` SMALLINT NOT NULL COMMENT '',
  PRIMARY KEY (`idtable`)  COMMENT '')
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alegria`.`tablereservation`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`tablereservation` ;

CREATE TABLE IF NOT EXISTS `alegria`.`tablereservation` (
  `idreservation` INT NOT NULL AUTO_INCREMENT COMMENT '',
  `date` DATE NOT NULL COMMENT '',
  `reservationtype` TINYINT NOT NULL COMMENT '',
  `guestnum` SMALLINT NOT NULL COMMENT '',
  `idmember` INT(11) NOT NULL COMMENT '',
  `idtable` INT(11) NOT NULL COMMENT '',
  `isadmin` TINYINT(1) NOT NULL COMMENT '',
  PRIMARY KEY (`idreservation`)  COMMENT '',
  INDEX `fk_tablereservation_member1_idx` (`idmember` ASC)  COMMENT '',
  INDEX `fk_tablereservation_lunchtables_idx` (`idtable` ASC)  COMMENT '',
  CONSTRAINT `fk_tablereservation_member1`
    FOREIGN KEY (`idmember`)
    REFERENCES `alegria`.`member` (`idmember`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_tablereservation_table1`
    FOREIGN KEY (`idtable`)
    REFERENCES `alegria`.`lunchtables` (`idtable`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alegria`.`provider_invoices`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`provider_invoices` ;

CREATE TABLE IF NOT EXISTS `alegria`.`provider_invoices` (
  `idprovider_invoices` VARCHAR(50) NOT NULL COMMENT '',
  `date` DATE NOT NULL COMMENT '',
  `total` DECIMAL(10,2) NOT NULL COMMENT '',
  `idprovider` INT NOT NULL COMMENT '',
  PRIMARY KEY (`idprovider_invoices`)  COMMENT '',
  INDEX `fk_provider_invoices_provider1_idx` (`idprovider` ASC)  COMMENT '',
  CONSTRAINT `fk_provider_invoices_provider1`
    FOREIGN KEY (`idprovider`)
    REFERENCES `alegria`.`provider` (`idprovider`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alegria`.`provider_invoices_product`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`provider_invoices_product` ;

CREATE TABLE IF NOT EXISTS `alegria`.`provider_invoices_product` (
  `provider_invoices_idprovider_invoices` VARCHAR(50) NOT NULL COMMENT '',
  `product_item_idproduct_item` INT(11) NOT NULL COMMENT '',
  `count` INT(11) NOT NULL COMMENT '',
  PRIMARY KEY (`provider_invoices_idprovider_invoices`, `product_item_idproduct_item`)  COMMENT '',
  INDEX `fk_table1_provider_invoices1_idx` (`provider_invoices_idprovider_invoices` ASC)  COMMENT '',
  INDEX `fk_table1_product_item1_idx` (`product_item_idproduct_item` ASC)  COMMENT '',
  CONSTRAINT `fk_table1_provider_invoices1`
    FOREIGN KEY (`provider_invoices_idprovider_invoices`)
    REFERENCES `alegria`.`provider_invoices` (`idprovider_invoices`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_table1_product_item1`
    FOREIGN KEY (`product_item_idproduct_item`)
    REFERENCES `alegria`.`product_item` (`idproduct_item`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alegria`.`ovens`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`ovens` ;

CREATE TABLE IF NOT EXISTS `alegria`.`ovens` (
  `idoven` INT(11) NOT NULL COMMENT '',
  `name` VARCHAR(45) NOT NULL COMMENT '',
  PRIMARY KEY (`idoven`)  COMMENT '')
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alegria`.`ovenreservation`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`ovenreservation` ;

CREATE TABLE IF NOT EXISTS `alegria`.`ovenreservation` (
  `idreservation` INT NOT NULL AUTO_INCREMENT COMMENT '',
  `date` DATE NOT NULL COMMENT '',
  `reservationtype` TINYINT NOT NULL COMMENT '',
  `idmember` INT(11) NOT NULL COMMENT '',
  `idoven` INT(11) NOT NULL COMMENT '',
  `isadmin` TINYINT(1) NOT NULL COMMENT '',
  PRIMARY KEY (`idreservation`)  COMMENT '',
  INDEX `fk_tablereservation_member1_idx` (`idmember` ASC)  COMMENT '',
  INDEX `fk_ovenreservation_oventables1_idx` (`idoven` ASC)  COMMENT '',
  CONSTRAINT `fk_tablereservation_member10`
    FOREIGN KEY (`idmember`)
    REFERENCES `alegria`.`member` (`idmember`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_ovenreservation_oventables1`
    FOREIGN KEY (`idoven`)
    REFERENCES `alegria`.`ovens` (`idoven`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alegria`.`fireplaces`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`fireplaces` ;

CREATE TABLE IF NOT EXISTS `alegria`.`fireplaces` (
  `idfireplace` INT(11) NOT NULL COMMENT '',
  `name` VARCHAR(45) NOT NULL COMMENT '',
  PRIMARY KEY (`idfireplace`)  COMMENT '')
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alegria`.`fireplacereservation`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`fireplacereservation` ;

CREATE TABLE IF NOT EXISTS `alegria`.`fireplacereservation` (
  `idreservation` INT NOT NULL AUTO_INCREMENT COMMENT '',
  `date` DATE NOT NULL COMMENT '',
  `reservationtype` TINYINT NOT NULL COMMENT '',
  `idmember` INT(11) NOT NULL COMMENT '',
  `idfireplace` INT(11) NOT NULL COMMENT '',
  `isadmin` TINYINT(1) NOT NULL COMMENT '',
  PRIMARY KEY (`idreservation`)  COMMENT '',
  INDEX `fk_tablereservation_member1_idx` (`idmember` ASC)  COMMENT '',
  INDEX `fk_fireplacereservation_fireplacetables1_idx` (`idfireplace` ASC)  COMMENT '',
  CONSTRAINT `fk_tablereservation_member100`
    FOREIGN KEY (`idmember`)
    REFERENCES `alegria`.`member` (`idmember`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_fireplacereservation_fireplacetables1`
    FOREIGN KEY (`idfireplace`)
    REFERENCES `alegria`.`fireplaces` (`idfireplace`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
