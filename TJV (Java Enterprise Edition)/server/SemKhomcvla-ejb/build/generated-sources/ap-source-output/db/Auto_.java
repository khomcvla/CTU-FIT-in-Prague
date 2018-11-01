package db;

import db.Oprava;
import javax.annotation.Generated;
import javax.persistence.metamodel.ListAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2018-01-01T16:04:02")
@StaticMetamodel(Auto.class)
public class Auto_ { 

    public static volatile SingularAttribute<Auto, String> modelA;
    public static volatile SingularAttribute<Auto, Integer> idA;
    public static volatile SingularAttribute<Auto, String> znackaA;
    public static volatile ListAttribute<Auto, Oprava> opravaList;

}