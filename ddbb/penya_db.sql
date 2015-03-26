CREATE SCHEMA IF NOT EXISTS `penya_db` DEFAULT CHARACTER SET utf8 COLLATE utf8_spanish_ci 

CREATE TABLE IF NOT EXISTS `penya_db`.`members` (
  `id_member` INT(11) NOT NULL,
  `name` VARCHAR(45) CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT NULL,
  `surname` VARCHAR(45) CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT NULL,
  `active` BINARY(1) NULL DEFAULT NULL,
  `card_num` INT(11) NOT NULL,
  `entry_date` DATE NULL DEFAULT NULL,
  `birth` DATE NULL DEFAULT NULL,
  `address` VARCHAR(120) CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT NULL,
  `zip_code` INT(11) NULL DEFAULT NULL,
  `town` VARCHAR(45) CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT NULL,
  `state` VARCHAR(45) CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT NULL,
  `tel` INT(11) NULL DEFAULT NULL,
  `tel2` INT(11) NULL DEFAULT NULL,
  `email` VARCHAR(45) CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT NULL,
  `bank_account` VARCHAR(45) CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NOT NULL,
  `postal_send` BINARY(1) NULL DEFAULT NULL,
  `notes` VARCHAR(250) CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT NULL,
  PRIMARY KEY (`id_member`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_spanish_ci
COMMENT = 'Member table with personal info'


CREATE TABLE IF NOT EXISTS `penya_db`.`tables` (
  `table_num` INT(11) NOT NULL,
  `capacity` INT(11) NULL DEFAULT NULL,
  `place` VARBINARY(10) NULL DEFAULT NULL,
  PRIMARY KEY (`table_num`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_spanish_ci
COMMENT = 'Reservation table number storage'


CREATE TABLE IF NOT EXISTS `penya_db`.`table_res` (
  `id` INT(11) NOT NULL,
  `fk_id_member` INT(11) NOT NULL,
  `fk_table_num` INT(11) NOT NULL,
  `date` DATE NULL DEFAULT NULL,
  `type` VARCHAR(45) CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT 'Lunch/Dinner',
  PRIMARY KEY (`id`),
  INDEX `fk_id_members_idx` (`fk_id_member` ASC),
  INDEX `fk_table_num_idx` (`fk_table_num` ASC),
  CONSTRAINT `fk_table_num`
    FOREIGN KEY (`fk_table_num`)
    REFERENCES `penya_db`.`tables` (`table_num`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_id_members`
    FOREIGN KEY (`fk_id_member`)
    REFERENCES `penya_db`.`members` (`id_member`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_spanish_ci
COMMENT = 'Table to reserve lunch/dinning table.'

CREATE TABLE IF NOT EXISTS `penya_db`.`invoices` (
  `id_inv` BIGINT(19) NOT NULL,
  `fk_id_member` INT(11) NOT NULL,
  `date` DATE NULL DEFAULT NULL,
  `bill` DECIMAL(6,2) NULL DEFAULT NULL,
  `type` VARCHAR(45) CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT NULL,
  `paid` BINARY(1) NULL DEFAULT NULL,
  `processed` BINARY(1) NULL DEFAULT NULL,
  PRIMARY KEY (`id_inv`),
  INDEX `fk_id_member_idx` (`fk_id_member` ASC),
  CONSTRAINT `fk_id_members_invoices`
    FOREIGN KEY (`fk_id_member`)
    REFERENCES `penya_db`.`members` (`id_member`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_spanish_ci
COMMENT = 'Member invoices table'


CREATE TABLE IF NOT EXISTS `penya_db`.`stock` (
  `id_stock` INT(11) NOT NULL,
  `name` VARCHAR(45) CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT NULL,
  `buy_price` DECIMAL(6,2) NULL DEFAULT NULL,
  `dose` INT(11) NULL DEFAULT NULL,
  PRIMARY KEY (`id_stock`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_spanish_ci
COMMENT = 'Table for stock.'

CREATE TABLE IF NOT EXISTS `penya_db`.`family` (
  `id_fam` INT(11) NOT NULL,
  `name` VARCHAR(45) CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT NULL,
  `fam_pict` LONGBLOB NULL DEFAULT NULL,
  `active` BINARY(1) NULL DEFAULT NULL,
  PRIMARY KEY (`id_fam`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_spanish_ci
COMMENT = 'Different families and their associated products'

CREATE TABLE IF NOT EXISTS `penya_db`.`stock_entry` (
  `id_stock_entry` INT(11) NOT NULL,
  `fk_stock` INT(11) NULL DEFAULT NULL,
  `ammount` INT(11) NULL DEFAULT NULL,
  `date` DATE NULL DEFAULT NULL,
  PRIMARY KEY (`id_stock_entry`),
  INDEX `fk_stock_stock_entry_idx` (`fk_stock` ASC),
  CONSTRAINT `fk_stock_stock_entry`
    FOREIGN KEY (`fk_stock`)
    REFERENCES `penya_db`.`stock` (`id_stock`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_spanish_ci
COMMENT = 'Table for stock entries.'

CREATE TABLE IF NOT EXISTS `penya_db`.`stock_prod` (
  `id_stock_prod` INT(11) NOT NULL,
  `fk_id_prod` INT(11) NULL DEFAULT NULL,
  `fk_id_stock` INT(11) NULL DEFAULT NULL,
  PRIMARY KEY (`id_stock_prod`),
  INDEX `fk_id_prod_idx` (`fk_id_prod` ASC),
  INDEX `fk_id_prod_stock_prod_idx` (`fk_id_prod` ASC),
  INDEX `fk_id_stock_stock_prod_idx` (`fk_id_stock` ASC),
  CONSTRAINT `fk_id_prod_stock_prod`
    FOREIGN KEY (`fk_id_prod`)
    REFERENCES `penya_db`.`products` (`id_prod`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_id_stock_stock_prod`
    FOREIGN KEY (`fk_id_stock`)
    REFERENCES `penya_db`.`stock` (`id_stock`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_spanish_ci
COMMENT = 'Intermediate table between products and stock'


CREATE TABLE IF NOT EXISTS `penya_db`.`products` (
  `id_prod` INT(11) NOT NULL,
  `desc` VARCHAR(45) CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT NULL,
  `prod_pict` LONGBLOB NULL DEFAULT NULL,
  `entry_date` DATE NULL DEFAULT NULL,
  `fk_id_family` INT(11) NULL DEFAULT NULL,
  `sell_price` DECIMAL(6,2) NULL DEFAULT NULL,
  `active` BINARY(1) NULL DEFAULT NULL,
  PRIMARY KEY (`id_prod`),
  INDEX `fk_id_fam_idx` (`fk_id_family` ASC),
  CONSTRAINT `fk_id_fam`
    FOREIGN KEY (`fk_id_family`)
    REFERENCES `penya_db`.`family` (`id_fam`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_spanish_ci
COMMENT = 'List of available products.'


CREATE TABLE IF NOT EXISTS `penya_db`.`prod_inv` (
  `id_prod_inv` BIGINT(19) NOT NULL,
  `fk_id_inv` BIGINT(19) NULL DEFAULT NULL,
  `fk_id_prod` INT(11) NULL DEFAULT NULL,
  `ammount` INT(11) NULL DEFAULT NULL,
  `date` DATE NULL DEFAULT NULL,
  PRIMARY KEY (`id_prod_inv`),
  INDEX `fk_id_inv_idx` (`fk_id_inv` ASC),
  INDEX `fk_id_prod_idx` (`fk_id_prod` ASC),
  CONSTRAINT `fk_id_prod`
    FOREIGN KEY (`fk_id_prod`)
    REFERENCES `penya_db`.`products` (`id_prod`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_id_inv`
    FOREIGN KEY (`fk_id_inv`)
    REFERENCES `penya_db`.`invoices` (`id_inv`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_spanish_ci
COMMENT = 'Intermediate table between products and invoices'




