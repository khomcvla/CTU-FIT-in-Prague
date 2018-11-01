/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package service;

import db.Oprava;
import java.util.List;
import javax.ejb.Local;

/**
 *
 * @author homya
 */
@Local
public interface OpravaFacadeLocal {

    void create(Oprava oprava);

    void edit(Oprava oprava);

    void remove(Oprava oprava);

    Oprava find(Object id);

    List<Oprava> findAll();

    List<Oprava> findRange(int[] range);

    int count();
    
}
