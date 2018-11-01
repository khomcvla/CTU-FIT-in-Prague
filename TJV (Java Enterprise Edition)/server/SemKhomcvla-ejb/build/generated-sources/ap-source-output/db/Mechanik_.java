package db;

import db.Oprava;
import javax.annotation.Generated;
import javax.persistence.metamodel.ListAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2018-01-01T16:04:02")
@StaticMetamodel(Mechanik.class)
public class Mechanik_ { 

    public static volatile SingularAttribute<Mechanik, Integer> idM;
    public static volatile ListAttribute<Mechanik, Oprava> opravaList;
    public static volatile SingularAttribute<Mechanik, String> jmenoM;
    public static volatile SingularAttribute<Mechanik, String> specializaceM;

}