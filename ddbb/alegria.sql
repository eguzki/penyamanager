SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

DROP SCHEMA IF EXISTS `alegria` ;
CREATE SCHEMA IF NOT EXISTS `alegria` DEFAULT CHARACTER SET utf8 ;
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
  `isAdmin` TINYINT(1) NOT NULL,
  `birth` DATE NULL,
  `address` VARCHAR(120) NULL,
  `zip_code` INT(11) NULL,
  `town` VARCHAR(45) NULL,
  `state` VARCHAR(45) NULL,
  `tel` INT(11) NULL,
  `tel2` INT(11) NULL,
  `email` VARCHAR(45) NULL,
  `bank_account` VARCHAR(45) NOT NULL,
  `postal_send` TINYINT(1) NULL,
  `notes` VARCHAR(45) NULL,
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
  `type` INT(11) NOT NULL,
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
-- Table `alegria`.`provider`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`provider` ;

CREATE TABLE IF NOT EXISTS `alegria`.`provider` (
  `idprovider` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(200) NOT NULL,
  `image` VARCHAR(200) NULL,
  `reg_date` DATE NULL,
  `phone` VARCHAR(45) NULL,
  PRIMARY KEY (`idprovider`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alegria`.`product_item`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`product_item` ;

CREATE TABLE IF NOT EXISTS `alegria`.`product_item` (
  `idproduct_item` INT(11) NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(200) NOT NULL,
  `image` VARCHAR(300) NULL,
  `active` TINYINT(1) NOT NULL,
  `reg_date` DATETIME NOT NULL,
  `idproduct_family` INT(11) NOT NULL,
  `price` DECIMAL(10,2) NOT NULL,
  `idprovider` INT(11) NOT NULL,
  `stock` INT(11) NOT NULL,
  PRIMARY KEY (`idproduct_item`),
  INDEX `fk_product_item_product_family_idx` (`idproduct_family` ASC),
  INDEX `fk_product_item_provider1_idx` (`idprovider` ASC),
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


-- -----------------------------------------------------
-- Table `alegria`.`deposit`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`deposit` ;

CREATE TABLE IF NOT EXISTS `alegria`.`deposit` (
  `iddeposit` INT(11) NOT NULL AUTO_INCREMENT,
  `state` INT(11) NOT NULL,
  `date` DATETIME NOT NULL,
  `total` DECIMAL(10,2) NOT NULL,
  `description` VARCHAR(120) NULL,
  `idmember` INT(11) NOT NULL,
  PRIMARY KEY (`iddeposit`),
  INDEX `fk_deposit_member1_idx` (`idmember` ASC),
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
  `idtable` INT(11) NOT NULL,
  `name` VARCHAR(45) NOT NULL,
  `guestnum` SMALLINT NOT NULL,
  PRIMARY KEY (`idtable`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alegria`.`tablereservation`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alegria`.`tablereservation` ;

CREATE TABLE IF NOT EXISTS `alegria`.`tablereservation` (
  `idtablereservation` INT NOT NULL AUTO_INCREMENT,
  `date` DATE NOT NULL,
  `reservationtype` TINYINT NOT NULL,
  `guestnum` SMALLINT NOT NULL,
  `idmember` INT(11) NOT NULL,
  `idtable` INT(11) NOT NULL,
  PRIMARY KEY (`idtablereservation`),
  INDEX `fk_tablereservation_member1_idx` (`idmember` ASC),
  INDEX `fk_tablereservation_lunchtables_idx` (`idtable` ASC),
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


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
