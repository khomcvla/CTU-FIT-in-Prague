package db;

import db.Auto;
import db.Mechanik;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2018-01-01T16:04:02")
@StaticMetamodel(Oprava.class)
public class Oprava_ { 

    public static volatile SingularAttribute<Oprava, Mechanik> idM;
    public static volatile SingularAttribute<Oprava, Integer> idO;
    public static volatile SingularAttribute<Oprava, Auto> idA;
    public static volatile SingularAttribute<Oprava, Integer> cenaO;
    public static volatile SingularAttribute<Oprava, String> diagnostikaO;

}