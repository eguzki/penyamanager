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
  PRIMARY KEY (`idproduct_item`),
  INDEX `fk_product_item_product_family_idx` (`idproduct_family` ASC),
  CONSTRAINT `fk_product_item_product_family`
    FOREIGN KEY (`idproduct_family`)
    REFERENCES `alegria`.`product_family` (`idproduct_family`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
